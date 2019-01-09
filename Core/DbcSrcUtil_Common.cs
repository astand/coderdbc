using CoderDbc.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CoderDbc.Core
{
    public class DbcSrcUtil_Common : CCodeGenerator
    {
        public override void Generate(List<MessageDescriptor> messages, string sourcepath, string sourceName, string HeadInfo)
        {
            _files.Dir = sourcepath;
            var sourcename = $"{sourceName}";
            _files.File = _files.Dir + "/" + sourcename + utilName;
            headFile.Clear();
            sourceFile.Clear();
            headContent.head.AppendLine(HeadInfo);
            headContent.head.AppendLine(TemplateSourceInfo.GuardInclude);
            headContent.head.AppendLine(TemplateSourceInfo.CPPGuardOpen);
            headContent.head.AppendLine(@"#include """ + sourcename + @".h""");
            headContent.head.AppendLine();
            headContent.head.AppendLine("// @dbccodeconf.h file should be placed in inc folder. If the user wants");
            headContent.head.AppendLine("// to allocate big DBC struct inside the driver - appropriate define (__DEF_xxxxx__)");
            headContent.head.AppendLine("// should be placed in this file");
            headContent.head.AppendLine("#include \"dbccodeconf.h\"");
            headContent.head.AppendLine();
            srcContent.head.AppendLine(HeadInfo);
            srcContent.head.AppendLine();
            srcContent.head.AppendLine("#include \"" + sourcename.ToLower() + utilName + ".h\"");
            srcContent.head.AppendLine();
            GenerateHeadBody(messages, sourcename);
            GenerateSourceBody(messages.Where(m => m.direction == Direction.Both || m.direction == Direction.Rx).ToList(), sourcename);
            headContent.end.AppendLine(TemplateSourceInfo.CPPGuardClose);
            /* -------------------------------------------- */
            headFile.Append(headContent.head.ToString());
            headFile.Append(headContent.body.ToString());
            headFile.Append(headContent.end.ToString());
            PrintHeadText();
            /* -------------------------------------------- */
            sourceFile.Append(srcContent.head.ToString());
            sourceFile.Append(srcContent.body.ToString());
            sourceFile.Append(srcContent.end.ToString());
            PrintSourceText();
        }

        private void GenerateHeadBody(List<MessageDescriptor> messages, string utilName)
        {
            this.utilName = utilName;
            PrintRxTypedefStruct(messages);
            PrintTxTypedefStruct(messages);

            if (messages.Where(m => m.direction == Direction.Both || m.direction == Direction.Rx).Count() > 0)
            {
                headContent.body.AppendLine();
                headContent.body.AppendLine($"uint32_t {utilName}_Receive({utilName}_{rxSuff}_t* _m, const uint8_t* _d, uint32_t _id);");
                headContent.body.AppendLine();
                headContent.body.AppendLine();
            }

            headContent.body.AppendLine($"// define @__DEF_{utilName.ToUpper()}__ in the @dbccodeconf.h file for allocation in utility source code.");
            headContent.body.AppendLine($"#ifdef __DEF_{utilName.ToUpper()}__");
            srcContent.head.AppendLine($"#ifdef __DEF_{utilName.ToUpper()}__" + Environment.NewLine);
            srcContent.body.AppendLine("#endif" + Environment.NewLine);
            headContent.end.AppendLine();
            headContent.end.AppendLine($"#endif");
            headContent.end.AppendLine();
        }

        protected virtual void GenerateSourceBody(List<MessageDescriptor> mgs, string utilName)
        {
            var orederedMsgs = mgs.OrderBy(m => m.MessageId).ToList();
            srcContent.body.AppendLine($"uint32_t {utilName}_Receive({utilName}_{rxSuff}_t* _m, const uint8_t* _d, uint32_t _id)");
            srcContent.body.AppendLine("{");
            srcContent.body.AppendLine("  uint32_t recid = 0;");
            srcContent.body.AppendLine();
            srcContent.body.AppendLine("  switch (_id)");
            srcContent.body.AppendLine("  {");

            foreach (var msg in orederedMsgs)
            {
                srcContent.body.AppendLine($"    case ({msg.PrintMsgIDName}):");
                srcContent.body.AppendLine($"      recid = Unpack_{msg.MessageName}_{utilName}(" + @"&" + $"(_m->{msg.MessageName}), _d);");
                srcContent.body.AppendLine( "      break;");
                srcContent.body.AppendLine();
            }

            srcContent.body.AppendLine("    default:");
            srcContent.body.AppendLine("      // frame is not conform to driver");
            srcContent.body.AppendLine("      ret = 0;");
            srcContent.body.AppendLine("      break;");
            srcContent.body.AppendLine("  }");
            srcContent.body.AppendLine();
            srcContent.body.AppendLine("  return recid;");
            srcContent.body.AppendLine("}");
            srcContent.body.AppendLine();
        }

        private void PrintRxTypedefStruct(List<MessageDescriptor> messages)
        {
            PrintTypeDef(rxSuff, Direction.Rx, messages);
        }

        private void PrintTxTypedefStruct(List<MessageDescriptor> messages)
        {
            PrintTypeDef(txSuff, Direction.Tx, messages);
        }

        private void PrintTypeDef(string v, Direction dir, List<MessageDescriptor> msgs)
        {
            var msgPresented = msgs.Where(m => m.direction == Direction.Both || m.direction == dir).Count();

            if (msgPresented == 0)
            {
                headContent.body.AppendLine($"// There is no any message detected with {v} direction.");
                return;
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
            var max_name = msgs.Aggregate(25, (max, cur) => max < (cur.MessageName.Length * 2) ? (cur.MessageName.Length * 2) : max);

            foreach (var msg in msgs)
            {
                if (msg.direction == Direction.Both || msg.direction == dir)
                {
                    headContent.body.Append(($"  {msg.MessageName}_t {msg.MessageName};").PadRight(max_name + 9));
                    headContent.body.Append("// TX [");
                    headContent.body.Append(($"{msg.Transmitter.ToString()}].").PadRight(10));
                    headContent.body.Append("RX [");

                    foreach (var item in msg.RecS)
                    {
                        headContent.body.Append($"{item} ");
                    }

                    headContent.body.AppendLine("].");
                }
            }

            headContent.body.AppendLine($"}} {utilName}_{v}_t;");
            headContent.body.AppendLine();
            headContent.end.AppendLine();
            headContent.end.AppendLine($"extern {utilName}_{v}_t {utilName}_{v};");
            /*-*/
            srcContent.body.AppendLine($"{utilName}_{v}_t {utilName}_{v};");
            srcContent.body.AppendLine();
        }

        protected string utilName = "_switchUtil";
        protected string rxSuff = "rx";
        protected string txSuff = "tx";
    }
}
