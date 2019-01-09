using CoderDbc.Models;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Security.AccessControl;
using System.Text;
using System.Threading.Tasks;

namespace CoderDbc.Core
{
    public class CSharpCodeGenerator
    {
        public GenerationSettings CodeSett { get; set; }

        public virtual void Generate(List<MessageDescriptor> messages, string sourcepath, string sourceName, string HeadInfo)
        {
            _files.Dir = sourcepath;
            var incName = $"{sourceName}";
            _files.File = _files.Dir + "/" + incName;
            FuncUtilName = incName;
            sourceFile.Clear();
            sourceFile.AppendLine($"using System;");
            sourceFile.AppendLine("");
            sourceFile.AppendLine("");
            sourceFile.AppendLine($"namespace {sourceName}");
            sourceFile.AppendLine("{");
            sourceFile.AppendLine($"  public class {sourceName}_t");
            sourceFile.AppendLine("  {");

            foreach (var message in messages)
            {
                sourceFile.AppendLine($"    public {message.MessageName}_t {message.MessageName} = new {message.MessageName}_t();");
            }

            sourceFile.AppendLine("  }");
            sourceFile.AppendLine();

            foreach (var message in messages)
            {
                sourceFile.AppendLine($"    public class {message.MessageName}_t ");
                sourceFile.AppendLine("    {");
                sourceFile.AppendLine($"      public const UInt32 {message.PrintMsgIDName} = {message.PrintMsgIDValue};");
                sourceFile.AppendLine($"      public const UInt32 {message.MessageName}_DLC = {message.DataLen};");

                foreach (var sig in message.Signals)
                {
                    string ret = cprint.PrintSignalPackExpression(sig);

                    if (ret != null)
                    {
                        sourceFile.AppendLine(ret);
                    }
                }

                foreach (var sig in message.Signals)
                {
                    sourceFile.AppendLine(cprint.PrintSignalType(sig));
                }

                SourceLine("      public UInt32 framecnt;");
                sourceFile.AppendLine("   }");
                sourceFile.AppendLine();
            }

            writer.Clear();
            tree = FillTreeLevel(messages, 0, messages.Count);
            SourceLine($"  public static class {sourceName}_Util ");
            SourceLine("{");
            SourceLine($"    public static UInt32 {sourceName}_Receive({sourceName}_t _m, Byte[] _d, UInt32 _id)");
            SourceLine("    {");
            SourceLine(" UInt32 ret = 0;");
            SourceLine();
            SourceLine(writer.WriteCode(tree, 1), false);
            SourceLine();
            SourceLine(" return ret;");
            SourceLine("    }");
            SourceLine();

            foreach (var msg in messages)
            {
                SourceLine($"    public static void Unpack_{msg.MessageName}_{incName}({msg.MessageName}_t _m, byte[] _d)");
                SourceLine("    {");
                GenerateUnpackFunction(msg);
                SourceLine("    }");
                SourceLine();
                SourceLine($"    public static UInt32 Pack_{msg.MessageName}_{incName}({msg.MessageName}_t _m, byte[] _d, byte _c)");
                SourceLine("    {");
                GeneratePackFunction(msg);
                SourceLine("    }");
            }

            SourceLine("  }");
            sourceFile.AppendLine("}");
            PrintSourceText();
        }

        protected ConditionalTree FillTreeLevel(List<MessageDescriptor> list, int l, int h)
        {
            var ret = new ConditionalTree();
            var span = h - l;
            var lowhalf = span / 2;
            var highhalf = span - lowhalf;

            if (span > 1)
            {
                ret.conditionalType = ConditionalType.Cond;

                if (lowhalf > 1)
                    ret.ConditionExpresion = "_id >= 0x" + list[l].MessageId.ToString("X") +
                                             "U && _id < 0x" + list[(l + lowhalf)].MessageId.ToString("X") + "U";
                else
                    ret.ConditionExpresion = "_id == " + list[l].PrintMsgIDValue;

                ret.High = FillTreeLevel(list, l, l + lowhalf);
                ret.Low = FillTreeLevel(list, l + lowhalf, h);
            }
            else
            {
                ret.conditionalType = ConditionalType.Express;
                var msg = list[l];
                ret.ConditionExpresion = "_id == " + msg.PrintMsgIDValue;
                ret.Code = $"Unpack_{msg.MessageName}_{FuncUtilName}(" + $"(_m.{msg.MessageName}), _d); ret = 1;";
            }

            return ret;
        }

        private void GenerateUnpackFunction(MessageDescriptor msg)
        {
            foreach (var sig in msg.Signals)
            {
                var sigLineExpression = $"  _m.{sig.FieldName} = ";
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

                sigLineExpression += $"({cprint.PrintType(sig.SigType)})({offsetExpr});";
                SourceLine(sigLineExpression);

                for (int i = 0; i < 8; i++)
                {
                    if (sig.SigToByte[i] == null)
                        continue;

                    if (msg.SigsToByteExpr[i] == null)
                        msg.SigsToByteExpr[i] = $"{sig.SigToByte[i]}";
                    else
                        msg.SigsToByteExpr[i] += $" | {sig.SigToByte[i]}";
                }
            }

            if (CodeSett.NeedFrameCounting)
                SourceLine("  _m.framecnt++;");
        }

        private void GeneratePackFunction(MessageDescriptor msg)
        {
            //SourceLine("  if (_c == 1) { (*(uint32_t*)(_d + 0)) = (*(uint32_t*)(_d + 4)) = 0; }");
            var clearbuf = String.Empty;
            clearbuf += "  if (_c == 1) { for (_c = 0; _c < ";
            clearbuf += $"8; ";
            clearbuf += "_d[_c++] = 0); }";
            SourceLine(clearbuf);
            SourceLine();

            for (int i = 0; i < 8; i++)
            {
                if (msg.SigsToByteExpr[i] != null)
                    SourceLine($"  _d[{i}] |= (byte)({msg.SigsToByteExpr[i]});");
            }

            SourceLine($"  return {msg.MessageName}_t.{msg.PrintMsgIDName};");
        }

        //protected void HeadLine(string str = "")
        //{
        //    headFile.Append(str + Environment.NewLine);
        //}

        protected void SourceLine(string str = "", bool lf = true)
        {
            sourceFile.Append(str + ((lf) ? (Environment.NewLine) : ("")));
        }

        //protected void PrintHeadText()
        //{
        //CheckFileExistance(".h");
        //File.WriteAllText(_files.File + ".h", headFile.ToString(), Encoding.UTF8);
        //File.SetAttributes(_files.File + ".h", FileAttributes.ReadOnly);
        //Debug.Write(headFile.ToString());
        //}


        protected void PrintSourceText()
        {
            CheckFileExistance(".cs");
            File.WriteAllText(_files.File + ".cs", sourceFile.ToString(), Encoding.UTF8);
            File.SetAttributes(_files.File + ".cs", FileAttributes.ReadOnly);
            //Debug.Write(sourceFile.ToString());
        }

        protected void CheckFileExistance(string fileext)
        {
            Directory.CreateDirectory(_files.Dir);

            try
            {
                if (File.Exists(_files.File + fileext))
                {
                    File.Delete(_files.File + fileext);
                }

                (File.Create(_files.File + fileext)).Close();
            }
            catch (Exception e)
            {
                Debug.WriteLine("Exception in file create: ");
                Debug.WriteLine(e.Message);
                Debug.WriteLine(e.ToString());
            }
        }

        //protected StringBuilder headFile = new StringBuilder(100000);
        protected StringBuilder sourceFile = new StringBuilder(100000);
        protected SourceFileDescriptor _files = new SourceFileDescriptor();
        string FuncUtilName;
        ConditionalTree tree;
        ConditionalTreeCWriter writer = new ConditionalTreeCWriter();
        CSharpSignalPrinter cprint = new CSharpSignalPrinter();
    }
}
