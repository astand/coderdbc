using CoderDbc.Core;
using CoderDbc.Models;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CoderDbc.Core
{
    public class DbcSourceCodeGenerator : CCodeGenerator
    {
        public DbcSourceCodeGenerator()
        {
        }


        public override void Generate(List<MessageDescriptor> messages, string sourcepath, string sourceName, string HeadInfo)
        {
            _files.Dir = sourcepath;
            var incName = $"{sourceName}";
            nameDrv_ = incName;
            List<string> funcSignatures = new List<string>();
            _files.File = _files.Dir + "/" + incName;
            headContent.head.AppendLine(HeadInfo);
            srcContent.head.AppendLine(HeadInfo);
            headContent.head.AppendLine(TemplateSourceInfo.GuardInclude);
            headContent.head.AppendLine(TemplateSourceInfo.CPPGuardOpen);
            srcContent.head.AppendLine();
            headContent.head.AppendLine(@"#include <stdint.h>");
            headContent.head.AppendLine("");
            headContent.head.AppendLine("// This file must define:");
            headContent.head.AppendLine("// base monitor struct");
            headContent.head.AppendLine("// function signature for CRC calculation");
            headContent.head.AppendLine("// function signature for getting system tick value (100 us step)");
            headContent.head.AppendLine(@"#include ""canmonitorutil.h""");
            headContent.head.AppendLine();
            headContent.head.AppendLine();

            if (CodeSett.Code.UseCANFrame == 1)
            {
                headContent.head.AppendLine($"// UseCANFrame is checked!");
                headContent.head.AppendLine($"// In this case the Pack_*name* function will take the pointer at");
                headContent.head.AppendLine($"// @__CoderDbcCanFrame_t__ data struct and the user must define this ");
                headContent.head.AppendLine($"// type. The best way is to define it (or typedef if already exists)");
                headContent.head.AppendLine($"// the CANFrame type with fields:");
                headContent.head.AppendLine($"//        -- MsgId : uint32_t");
                headContent.head.AppendLine($"//        -- DLC : uint8_t");
                headContent.head.AppendLine($"//        -- IDE : uint8_t");
                headContent.head.AppendLine($"//        -- Data : uint8_t* (with minimum 8 bytes capacity)");
                headContent.head.AppendLine("");
                headContent.head.AppendLine($"// Do it in the common dbc config file");
                headContent.head.AppendLine($"#include \"dbccodeconf.h\"");
                headContent.head.AppendLine("");
            }

            headContent.head.AppendLine();
            srcContent.head.AppendLine("#include \"" + incName.ToLower() + ".h\"");

            if (CodeSett.Code.UseMonitors == 1)
            {
                fmonFile = "fmon-" + incName.ToLower() + ".h";
                srcContent.head.AppendLine("");
                srcContent.head.AppendLine("// This include contains the prototypes of the functions that");
                srcContent.head.AppendLine("// perform the main monitor checkin and notify other clients");
                srcContent.head.AppendLine("// (e.g. DTC, logic behaviour etc)");
                srcContent.head.AppendLine("// the *.c source code must be created by end-user or linkage error!");
                srcContent.head.AppendLine($"#include \"{fmonFile}\"");
                // clear content
                fmon_base_content.Clear();
                fmon_funcs_proto.Clear();


            }

            srcContent.head.AppendLine();

            foreach (var msg in messages)
            {
                srcContent.body.AppendLine("// --------------------------------------------------------------------------");
                var function = String.Empty;
                PrintHeadTypedef(msg);
                function = $"uint32_t Unpack_{msg.MessageName}_{incName}({msg.MessageName}_t* _m, const uint8_t* _d, uint8_t dlc_)";
                funcSignatures.Add(function + ";");
                srcContent.body.AppendLine(function);
                srcContent.body.AppendLine("{");
                GenerateUnpackFunction(msg);
                srcContent.body.AppendLine("}");
                srcContent.body.AppendLine();

                if (CodeSett.Code.UseCANFrame == 1)
                {
                    // the pointer on the __CoderDbcCanFrame_t__ must be typedefed and
                    // it is used as a parameter to pass in the function
                    function = $"uint32_t Pack_{msg.MessageName}_{incName}(const {msg.MessageName}_t* _m, __CoderDbcCanFrame_t__* cframe)";
                    funcSignatures.Add(function + ";");
                    srcContent.body.AppendLine(function);
                    srcContent.body.AppendLine("{");
                    GenPack_withCanFrame(msg);
                    srcContent.body.AppendLine("}");
                    srcContent.body.AppendLine();
                }
                else
                {
                    function = $"uint32_t Pack_{msg.MessageName}_{incName}(const {msg.MessageName}_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)";
                    funcSignatures.Add(function + ";");
                    srcContent.body.AppendLine(function);
                    srcContent.body.AppendLine("{");
                    GenPack_withStdParams(msg);
                    srcContent.body.AppendLine("}");
                    srcContent.body.AppendLine();
                }
            }

            foreach (var sig in funcSignatures)
            {
                headContent.body.AppendLine(sig);
            }

            headContent.end.AppendLine(TemplateSourceInfo.CPPGuardClose);
            /* ------------------------------------------------------------------ */
            headFile.Clear();
            headFile.Append(headContent.head.ToString());
            headFile.Append(headContent.body.ToString());
            headFile.Append(headContent.end.ToString());
            PrintHeadText();
            /* ------------------------------------------------------------------ */
            sourceFile.Clear();
            sourceFile.Append(srcContent.head.ToString());
            sourceFile.Append(srcContent.body.ToString());
            sourceFile.Append(srcContent.end.ToString());
            PrintSourceText();
            /* ------------------------------------------------------------------ */
            monitorFile.Clear();
            var dt = DateTime.Now;
            monitorFile.AppendLine($"// Generated at @{dt.ToString("F")}. Ver: 0.1");
            monitorFile.Append(CanMonitorConfigContent);
            CreateMonitorTypeDefinesFile(_files.Dir + "/canmonitorutil.h", monitorFile);
            // This function will create (overwrite) the header that contains all the
            // prototypes for the monitoring functions
            // OR
            // Delete the file if the setting for UseMonitors != 1
            CreateMonitorFunctionsProtoFile(_files.Dir);
        }


        private void GenerateUnpackFunction(MessageDescriptor msg)
        {
            for (int i = 0; i < msg.SigsToByteExpr.Length; i++)
                msg.SigsToByteExpr[i] = null;

            foreach (var sig in msg.Signals)
            {
                var sigLineExpression = $"  _m->{sig.FieldName} = ";
                var offsetExpr = cprint.PrintUnpackFunctionBody(sig);

                if (CodeSett.NeedOffsetCalc)
                {
                    if (sig.Offset < 0)
                    {
                        offsetExpr = ($"({cprint.PrintUnpackFunctionBody(sig)}) - {Math.Abs(sig.RawOffset)}");
                    }
                    else if (sig.Offset > 0)
                    {
                        offsetExpr = ($"({cprint.PrintUnpackFunctionBody(sig)}) + {Math.Abs(sig.RawOffset)}");
                    }
                }

                sigLineExpression += offsetExpr + ";";
                srcContent.body.AppendLine(sigLineExpression);

                for (int i = 0; i < 8; i++)
                {
                    // update or create start of PackExpression for this signal for each byte
                    if (sig.SigToByte[i] == null)
                        continue;

                    if (msg.SigsToByteExpr[i] == null)
                        msg.SigsToByteExpr[i] = $"{sig.SigToByte[i]}";
                    else
                        msg.SigsToByteExpr[i] += $" | {sig.SigToByte[i]}";
                }
            }

            if (CodeSett.Code.UseMonitors == 1)
            {
                PrintMonitorsForSignals(msg);
            }

            srcContent.body.AppendLine($"  return {msg.PrintMsgIDName};");
        }


        private void GenPack_withCanFrame(MessageDescriptor msg)
        {
            //srcContent.body.AppendLine("  if (_c == 1) { (*(uint32_t*)(_d + 0)) = (*(uint32_t*)(_d + 4)) = 0; }");
            var clearbuf = String.Empty;
            clearbuf += "  uint8_t i; for (i = 0; i < ";
            clearbuf += $"{msg.MessageName}_DLC; ";
            clearbuf += "cframe->Data[i++] = 0);";
            srcContent.body.AppendLine(clearbuf);
            srcContent.body.AppendLine();

            for (int i = 0; i < 8; i++)
            {
                if (msg.SigsToByteExpr[i] != null)
                    srcContent.body.AppendLine($"  cframe->Data[{i}] |= {msg.SigsToByteExpr[i]};");
            }

            srcContent.body.AppendLine("");
            srcContent.body.AppendLine($"  cframe->MsgId = {msg.PrintMsgIDName};");
            srcContent.body.AppendLine($"  cframe->DLC = {msg.DataLen};");
            srcContent.body.AppendLine($"  cframe->IDE = {msg.IsExtended};");
            srcContent.body.AppendLine($"  return {msg.PrintMsgIDName};");
        }


        private void GenPack_withStdParams(MessageDescriptor msg)
        {
            //srcContent.body.AppendLine("  if (_c == 1) { (*(uint32_t*)(_d + 0)) = (*(uint32_t*)(_d + 4)) = 0; }");
            var clearbuf = String.Empty;
            clearbuf += "  uint8_t i; for (i = 0; i < ";
            clearbuf += $"{msg.MessageName}_DLC; ";
            clearbuf += "_d[i++] = 0);";
            srcContent.body.AppendLine(clearbuf);
            srcContent.body.AppendLine();

            for (int i = 0; i < 8; i++)
            {
                if (msg.SigsToByteExpr[i] != null)
                    srcContent.body.AppendLine($"  _d[{i}] |= {msg.SigsToByteExpr[i]};");
            }

            srcContent.body.AppendLine($"  *_len = {msg.DataLen}; *_ide = {msg.IsExtended};");
            srcContent.body.AppendLine($"  return {msg.PrintMsgIDName};");
        }


        public void PrintMonitorsForSignals(MessageDescriptor msg)
        {
            srcContent.body.AppendLine("  // check DLC correctness");
            srcContent.body.AppendLine($"  _m->mon1.dlc_error = (dlc_ < {msg.MessageName}_DLC);");

            // check_sum_error
            if (msg.RollSig != null && msg.RollSig.LengthBit <= 8)
            {
                srcContent.body.AppendLine($"  // rolling counter validation. The bit @roll_error is 1 when rolling failure.");
                srcContent.body.AppendLine($"  _m->mon1.roll_error = (_m->mon1.roll_expect != _m->{msg.RollSig.FieldName});");
                srcContent.body.Append($"  _m->mon1.roll_expect = ((_m->{msg.RollSig.FieldName} + 1) & ");
                srcContent.body.AppendLine($"0x{((Int32)Math.Pow(2, msg.RollSig.LengthBit) - 1).ToString("X2")}U);");
            }

            if (msg.CsmSig != null && msg.CsmSig.LengthBit <= 8)
            {
                srcContent.body.AppendLine("  // Check the checksum value");
                srcContent.body.Append($"  _m->mon1.checksum_error = (GetCrcValueForArray(_d, ");
                srcContent.body.Append($"{msg.MessageName}_DLC - 1, {msg.CsmType}, 0) != ");
                srcContent.body.AppendLine($"(_m->{msg.CsmSig.FieldName}));");
            }

            srcContent.body.AppendLine($"  _m->mon1.last_cycle = {GetTickFuncName}();");
            srcContent.body.AppendLine("  _m->mon1.frame_cnt++;");
            var Fmon_func = "FMon_" + msg.MessageName + ((nameDrv_?.Length > 0) ? $"_{nameDrv_}" : "");
            srcContent.body.AppendLine("");
            srcContent.body.AppendLine($"  // Calling monitor function for @{msg.MessageName}");
            srcContent.body.AppendLine($"  {Fmon_func}(&_m->mon1);");
            // put the prototype in the header of monitors functions
            fmon_funcs_proto.Add($"void { Fmon_func}(FrameMonitor_t * _mon); ");
        }



        private void CreateMonitorTypeDefinesFile(string v, StringBuilder mfile)
        {
            if (File.Exists(v))
            {
                File.Delete(v);
            }

            (File.Create(v)).Close();
            File.WriteAllText(v, mfile.ToString(), Encoding.UTF8);
            File.SetAttributes(v, FileAttributes.ReadOnly);
        }


        private void CreateMonitorFunctionsProtoFile(string dir)
        {
            var monfilepath = dir + "\\" + fmonFile;

            if (File.Exists(monfilepath))
            {
                File.Delete(monfilepath);
            }

            if (CodeSett.Code.UseMonitors == 1)
            {
                fmon_base_content.AppendLine($"// Generated at @{DateTime.Now.ToString("F")}. Ver: 0.1");
                fmon_base_content.AppendLine(TemplateSourceInfo.GuardInclude);
                fmon_base_content.AppendLine(TemplateSourceInfo.CPPGuardOpen);
                fmon_base_content.AppendLine("#include <stdint.h>");
                fmon_base_content.AppendLine("");
                fmon_base_content.AppendLine(@"#include ""canmonitorutil.h""");
                fmon_base_content.AppendLine("");
                fmon_base_content.AppendLine("// This file contains the prototypes of all the functions that will be called");
                fmon_base_content.AppendLine("// from each Unpack_*name* function to detect DBC related errors");
                fmon_base_content.AppendLine("// It is the user responsibility to defined these functions in the");
                fmon_base_content.AppendLine("// separated .c file. If it won't be done the linkage error will happen");
                fmon_funcs_proto.Sort();

                foreach (var fproto in fmon_funcs_proto)
                {
                    fmon_base_content.AppendLine(fproto);
                }

                fmon_base_content.AppendLine(TemplateSourceInfo.CPPGuardClose);
                // create new monitor file
                (File.Create(monfilepath)).Close();
                File.WriteAllText(monfilepath, fmon_base_content.ToString());
                File.SetAttributes(monfilepath, FileAttributes.ReadOnly);
            }
        }


        private void PrintHeadTypedef(MessageDescriptor msg)
        {
            headContent.body.AppendLine($"// def @{msg.MessageName} CAN Message ({msg.MessageId})");
            headContent.body.AppendLine($"#define {msg.MessageName}_IDE ({msg.IsExtended}U)");
            headContent.body.AppendLine($"#define {msg.MessageName}_DLC ({msg.DataLen}U)");
            headContent.body.AppendLine($"#define {msg.PrintMsgIDName} ({msg.PrintMsgIDValue})");

            if (msg.CycTime > 0)
            {
                headContent.body.AppendLine($"#define {msg.MessageName}_CYC ({msg.CycTime}U)");
            }

            if (msg.CommentText != null)
            {
                headContent.body.AppendLine("// -- " + msg.CommentText);
            }

            foreach (var sig in msg.Signals)
            {
                string ret = cprint.PrintSignalPackExpression(sig);

                if (ret != null)
                {
                    headContent.body.AppendLine(ret);
                }
            }

            if (CodeSett.Packed.Length > 0)
            {
                headContent.body.AppendLine($"typedef {CodeSett.Packed} struct");
            }
            else
            {
                headContent.body.AppendLine($"typedef struct");
            }

            headContent.body.AppendLine("{");
            var max_len = msg.Signals.Aggregate(27, (max, cur) => max < cur.FieldName.Length ? cur.FieldName.Length : max);

            foreach (var sig in msg.Signals)
            {
                headContent.body.AppendLine(cprint.PrintSignalType(sig, max_len, CodeSett.Code.UseBitField == 1));
            }

            if (CodeSett.Code.UseMonitors == 1)
                headContent.body.AppendLine("  FrameMonitor_t mon1;");

            headContent.body.AppendLine("} " + msg.MessageName + "_t;");
            headContent.body.AppendLine();
        }

        private StringBuilder fmon_base_content = new StringBuilder(4096);

        private List<string> fmon_funcs_proto = new List<string>();

        CSignalPrinter cprint = new CSignalPrinter();

        private string nameDrv_ = "";
        private string fmonFile = "";

        private static readonly string GetTickFuncName = "GetSystemTick";

        private readonly string CanMonitorConfigContent =
            @"// This file has the common name. When a few DBC source code drivers are used you need to
// provide only one copy of it.
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern ""C"" {
#endif

enum DbcCanCrcMethods {
  kCRCUndefined = 0,
  kSAEJ1850 = 1,
  kXOR8 = 2,
  kXOR4 = 3
};

typedef struct {
  // @last_cycle keeps tick-value when last frame was received
  uint32_t last_cycle;

  // @timeout_cycle keeps maximum timeout for frame
  uint32_t timeout_cycle;

  // @frame_cnt keeps count of all the received frames
  uint32_t frame_cnt;

  // this expected @RC value
  uint8_t roll_expect;

  // setting up @roll_error bit indicates roll counting fail. Bit is not clearing automatically!
  uint32_t roll_error : 1;

  // setting up @checksum_error bit indicates checksum checking failure. Bit is not clearing automatically!
  uint32_t checksum_error : 1;

  // setting up @cycle_error bit indicates that time was overrunned. Bit is not clearing automatically!
  uint32_t cycle_error : 1;

  // setting up @dlc_error bit indicates that the actual DLC of CAN frame is not equal to defined by CAN matrix!
  uint32_t dlc_error : 1;

} FrameMonitor_t;

/* ----------------------------------------------------------------------------- */
// If your CAN matrix has the messages that must be controlled with @Checksum calculation
// then the calculation function must be presented in your code :

uint8_t GetCrcValueForArray(const uint8_t* d, uint8_t len, uint32_t method, uint8_t op);

// @d - array for CRC calculation
// @len - amount of bytes for calculation
// @method - CRC algorythm. It can be enum value or define and must be defined outside this scope
// @op - not defined yet

/* ----------------------------------------------------------------------------- */
// this function will be called when unpacking is performing. Value will be saved
// in @last_cycle variable
uint32_t " + GetTickFuncName + @"(void);


#ifdef __cplusplus
}
#endif
";


    }
}
