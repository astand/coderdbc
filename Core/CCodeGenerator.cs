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
    public abstract class CCodeGenerator
    {

        public GenerationSettings CodeSett { get; set; }

        public abstract void Generate(List<MessageDescriptor> messages, string sourcepath, string sourceName, string HeadInfo);

        //protected void HeadLine(string str = "")
        //{
        //    headFile.Append(str + Environment.NewLine);
        //}

        //protected void SourceLine(string str = "", bool lf = true)
        //{
        //    sourceFile.Append(str + ((lf) ? (Environment.NewLine) : ("")));
        //}

        protected void PrintHeadText()
        {
            CheckFileExistance(".h");
            File.WriteAllText(_files.File + ".h", headFile.ToString(), Encoding.UTF8);
            File.SetAttributes(_files.File + ".h", FileAttributes.ReadOnly);
            //Debug.Write(headFile.ToString());
        }


        protected void PrintSourceText()
        {
            CheckFileExistance(".c");
            File.WriteAllText(_files.File + ".c", sourceFile.ToString(), Encoding.UTF8);
            File.SetAttributes(_files.File + ".c", FileAttributes.ReadOnly);
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

        protected FileSectionPrinter headContent = new FileSectionPrinter();
        protected FileSectionPrinter srcContent = new FileSectionPrinter();
        protected StringBuilder headFile = new StringBuilder(100000);
        protected StringBuilder sourceFile = new StringBuilder(100000);
        protected StringBuilder monitorFile = new StringBuilder(10000);
        protected SourceFileDescriptor _files = new SourceFileDescriptor();
    }
}
