using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CoderDbc.Core
{
    public class FileSectionPrinter
    {
        public StringBuilder head;
        public StringBuilder body;
        public StringBuilder end;

        public FileSectionPrinter()
        {
            head = new StringBuilder(10000);
            body = new StringBuilder(10000);
            end = new StringBuilder(10000);
        }
    }
}
