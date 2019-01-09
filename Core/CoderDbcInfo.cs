using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace CoderDbc.Core
{
    public static class CoderDbcInfo
    {
        static CoderDbcInfo()
        {
            Vers = Assembly.GetCallingAssembly().GetName().Version;
        }
        public static Version Vers { get; }
    }

}
