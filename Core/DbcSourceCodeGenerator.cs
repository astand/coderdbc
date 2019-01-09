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

            if (CodeSett.NeedFrameCounting)
                srcContent.body.AppendLine("  _m->framecnt++;");

            srcContent.body.AppendLine($"  return {msg.PrintMsgIDName};");
        }

        private void GeneratePackFunction(MessageDescriptor msg)
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

        public override void Generate(List<MessageDescriptor> messages, string sourcepath, string sourceName, string HeadInfo)
        {
            _files.Dir = sourcepath;
            var incName = $"{sourceName}";
            List<string> funcSignatures = new List<string>();
            _files.File = _files.Dir + "/" + incName;
            headContent.head.AppendLine(HeadInfo);
            srcContent.head.AppendLine(HeadInfo);
            headContent.head.AppendLine(TemplateSourceInfo.GuardInclude);
            headContent.head.AppendLine(TemplateSourceInfo.CPPGuardOpen);
            srcContent.head.AppendLine();
            headContent.head.AppendLine($"#include <stdint.h>");
            headContent.head.AppendLine();
            srcContent.head.AppendLine("#include \"" + incName.ToLower() + ".h\"");
            srcContent.head.AppendLine();

            foreach (var msg in messages)
            {
                srcContent.body.AppendLine("// --------------------------------------------------------------------------");
                var function = String.Empty;
                PrintHeadTypedef(msg);
                function = $"uint32_t Unpack_{msg.MessageName}_{incName}({msg.MessageName}_t* _m, const uint8_t* _d)";
                funcSignatures.Add(function + ";");
                srcContent.body.AppendLine(function);
                srcContent.body.AppendLine("{");
                GenerateUnpackFunction(msg);
                srcContent.body.AppendLine("}");
                srcContent.body.AppendLine();
                function = $"uint32_t Pack_{msg.MessageName}_{incName}(const {msg.MessageName}_t* _m, uint8_t* _d, uint8_t* _len, uint8_t* _ide)";
                funcSignatures.Add(function + ";");
                srcContent.body.AppendLine(function);
                srcContent.body.AppendLine("{");
                GeneratePackFunction(msg);
                srcContent.body.AppendLine("}");
                srcContent.body.AppendLine();
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
                headContent.body.AppendLine(cprint.PrintSignalType(sig, max_len));
            }

            if (CodeSett.NeedFrameCounting)
                headContent.body.AppendLine("  uint32_t framecnt;");

            headContent.body.AppendLine("} " + msg.MessageName + "_t;");
            headContent.body.AppendLine();
        }

        CSignalPrinter cprint = new CSignalPrinter();
    }
}
