using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace CoderDbc.Models
{
    public enum Direction
    {
        None, Tx, Rx, Both, NoCode
    }

    public class MessageDescriptor
    {
        public string MessageName { get; set; }

        public int DataLen { get; set; }

        public UInt32 MessageId { get; set; }

        public Byte MsgHiBits { get; set; }

        public byte IsExtended { get; set; }

        public UInt32 CycTime { get; set; } = 0;

        public Direction direction { get; set; } = Direction.None;

        public String Transmitter { get; set; } = null;

        public List<String> RecS { get; set; } = new List<string>();

        public List<SignalBitsDesc> Signals { get; set; } = new List<SignalBitsDesc>();

        public String[] SigsToByteExpr { get; set; } = new String[8];

        public String CommentText { get; set; }

        internal void AddSignals(List<SignalBitsDesc> list)
        {
            foreach (var sig in list)
            {
                foreach (var rx in sig.Receivers)
                {
                    if (rx.Length > 0 && RecS.Contains(rx) == false)
                    {
                        RecS.Add(rx);
                    }
                }
            }

            RecS = RecS.OrderBy(s => s).ToList();
            Signals = list;
        }

        public string PrintRecS()
        {
            var ret = "";

            for (int i = 0; i < RecS.Count(); i++)
            {
                if (i > 0)
                {
                    ret += ", " + RecS[i];
                }
                else
                {
                    ret += RecS[i];
                }
            }

            return ret;
        }

        public bool ParseVectorDbcLine(string line)
        {
            if (line.StartsWith("BO_ "))
            {
                var raw = Regex.Split(line, VectorMessageDbcPattern);
                MessageName = raw[2];
                MessageId = UInt32.Parse(raw[1]);
                DataLen = Int32.Parse(raw[4]);
                Transmitter = raw[5];

                if ((MessageId & 0x60000000) != 0 || DataLen == 0 || DataLen > 8)
                    return false;

                MsgHiBits = ((byte)((MessageId >> 29) & 0x04));

                if (MsgHiBits == 0x04)
                    IsExtended = 1;

                MessageId &= (0x1fffFFFF);
                return true;
            }

            return false;
        }

        public override string ToString()
        {
            return $"Msg: {MessageName} ID[{MessageId:X8}] len={DataLen}";
        }

        public string PrintMsgIDName => $"{MessageName}_CANID";

        public string PrintMsgIDValue => $"0x{(MessageId & 0x1fffFFFF).ToString("X")}U";

        public SignalBitsDesc RollSig { get; internal set; }

        public SignalBitsDesc CsmSig { get; internal set; }
        public string CsmType { get; internal set; }

        static readonly string VectorMessageDbcPattern = @"[^A-Za-z0-9_.-]";

    }
}
