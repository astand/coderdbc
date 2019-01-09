using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CoderDbc.Core
{
    public static class DbcFileProvider
    {
        public static StringReader Dbc(string file)
        {
            var str = String.Empty;
            str = File.ReadAllText(file);
            StringReader rd = new StringReader(str);
            return rd;
        }
    }
}
