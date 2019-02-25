using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CoderDbc.Core
{
    public enum ConditionalType { Cond, Express, Single };

    public class ConditionalTree
    {
        public ConditionalTree() { }

        public ConditionalTree High { get; set; }

        public ConditionalTree Low { get; set; }

        public ConditionalType conditionalType = ConditionalType.Cond;

        public string ConditionExpresion { get; set; }

        public string UtilCodeBody { get; set; }
    };

    public class ConditionalTreeCWriter
    {
        public string WriteCode(ConditionalTree tree, int indent)
        {
            if (tree != null)
            {
                if (tree.conditionalType == ConditionalType.Cond)
                {
                    PrintCode($"if ({tree.ConditionExpresion}) {{", indent);
                    WriteCode(tree.High, indent + 1);

                    if (tree.Low != null)
                    {
                        if (tree.Low.conditionalType == ConditionalType.Express)
                        {
                            PrintCode($"}} else if ({tree.Low.ConditionExpresion}) {{", indent);
                        }
                        else
                        {
                            PrintCode("} else {", indent);
                        }

                        WriteCode(tree.Low, indent + 1);
                    }
                    else
                    {
                        PrintCode("}", indent);
                    }

                    if (tree.Low != null)
                    {
                        PrintCode("}", indent);
                    }
                }
                else
                {
                    PrintCode($"{tree.UtilCodeBody}", indent);
                }
            }

            return sb.ToString();
        }



        public void Clear()
        {
            sb.Clear();
        }

        void PrintCode(string s, int indent)
        {
            s = "".PadRight(indent) + s;
            Debug.WriteLine(s);
            sb.AppendLine(s);
        }

        StringBuilder sb = new StringBuilder(2048);
    };
}
