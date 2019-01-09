using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace CoderDbc.Core
{
    public class CommentDescription
    {
        public CommentType Type;
        public UInt32 MsgId;
        public String NodeName;
        public String SigName;
        public String Text;
    }

    public enum CommentType { NodeComment, MessageComment, SignalComment }

    public class Commenter
    {
        public bool IsCollectingData { get; set; }

        public bool PassString(string line)
        {
            if (line.StartsWith("CM_ "))
            {
                IsCollectingData = true;
                var strs = Regex.Split(line, @"[""]+");
                var directs = Regex.Split(strs[0], @"[ ]+");

                if (directs[1] == "SG_")
                {
                    Info.Type = CommentType.SignalComment;
                    Info.MsgId = UInt32.Parse(directs[2]) & (~(1 << 31));
                    Info.SigName = directs[3];
                }
                else if (directs[1] == "BO_")
                {
                    Info.Type = CommentType.MessageComment;
                    Info.MsgId = UInt32.Parse(directs[2]) & (~(1 << 31));
                }
                else if (directs[1] == "BU_")
                {
                    Info.Type = CommentType.NodeComment;
                    Info.NodeName = directs[2];
                }
                else
                {
                    IsCollectingData = false;
                }

                Info.Text = strs[1];

                if (strs.Length == 3)
                {
                    IsCollectingData = false;
                    return true;
                }
            }
            else if (IsCollectingData == true)
            {
                var strs = Regex.Split(line, @"[""]+");
                Info.Text += "  " + strs[0];

                if (strs.Length > 1)
                {
                    IsCollectingData = false;
                    return true;
                }
            }

            return false;
        }

        //public CommentType type;
        //public string NodeName;
        //public UInt32 MsgId;

        //public List<string> Comments;

        public CommentDescription Info { get; set; } = new CommentDescription();
    }

    public class ValParser
    {
        public String Text;
        public UInt32 MsgId;
        public String SigName;

        public bool PassString(string line)
        {
            var strOut = Regex.Matches(line, @"""[^""]+""|[\w]+", RegexOptions.Multiline)
                         .Cast<Match>()
                         .Select(c => c.Value).ToList();
            MsgId = UInt32.Parse(strOut[1]) & (~(1 << 31));
            SigName = strOut[2];
            var pairs = (strOut.Count - 3) / 2;
            Text = String.Empty;

            for (int i = 0; i < pairs; i++)
            {
                Text += $"  // {strOut[3 + i * 2]} - {strOut[3 + i * 2 + 1]} {Environment.NewLine}";
            }

            return true;
        }
    }
}
