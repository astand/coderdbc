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
            try
            {
                Vers = Assembly.GetAssembly(typeof(CoderDbcInfo)).GetName().Version;
            }
            catch (Exception e)
            {
                 Status = e.Message;
            }
        }

        public static Version Vers { get; }
        public static String Status { get; }
    }

}
