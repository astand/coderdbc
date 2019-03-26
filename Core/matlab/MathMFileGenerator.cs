using CoderDbc.Models;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CoderDbc.Core
{
    public class MathMFileGenerator : CCodeGenerator
    {
        public override void Generate(List<MessageDescriptor> messages, string sourcepath, string sourceName, string HeadInfo)
        {
            _files.Dir = sourcepath;
            var incName = $"{sourceName}";
            _files.File = _files.Dir + "/" + incName + "_mathlab";
            headFile.Clear();

            foreach (var msg in messages)
            {
                headFile.Append(print.PrintMathData(msg));
            }

            headFile.Append("Hello world");
            PrintHeadText();
        }

        MathSignalPrinter print = new MathSignalPrinter();
    }
}
