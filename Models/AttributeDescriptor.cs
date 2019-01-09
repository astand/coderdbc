using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace CoderDbc.Models
{
    public class AttrDescriptor
    {
        public UInt32 CycTime { get; set; } = 0;

        public UInt32 MsgId { get; set; } = 0;

        public bool ParseBA_(string line)
        {
            if (!line.Contains("GenMsgCycleTime")) return false;

            var strs = Regex.Split(line, @"[^A-Za-z0-9_]+");

            if (strs.Length != 6) return false;

            var value = 0U;

            if (UInt32.TryParse(strs[3], out value))
            {
                MsgId = value & 0x1fffFFFF;
            }
            else return false;

            if (UInt32.TryParse(strs[4], out value))
            {
                CycTime = value;
            }
            else return false;

            return true;
        }
    }
}
