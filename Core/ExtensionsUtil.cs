using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CoderDbc.Core
{
    public static class ExtensionsUtil
    {
        public static string ToViewable(this double x)
        {
            var ret = "";

            if (x - Math.Truncate(x) == 0)
            {
                ret = x.ToString("F0");
            }
            else
            {
                ret = x.ToString();
            }

            return ret;
        }

    }
}
