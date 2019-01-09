using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace CoderDbc
{
    [DataContract]
    public class GenerationSettings
    {
        [DataMember]
        public bool NeedFrameCounting { get; set; } = false;

        [DataMember]
        public bool NeedOffsetCalc { get; set; } = true;

        [DataMember]
        public bool NeedMathLabGeneration { get; set; } = false;

        [DataMember]
        public bool NeedSwitch { get; set; } = true;

        [DataMember]
        public bool NeedBin { get; set; } = true;

        [DataMember]
        public bool RewriteSource { get; set; } = false;

        [DataMember]
        public bool Opt2 { get; set; } = true;

        [DataMember]
        public string Packed { get; set; } = "";

        [DataMember]
        public string OptStr1 { get; set; } = "";

        [DataMember]
        public string OptStr2 { get; set; } = "";

        [DataMember]
        public List<UInt32> Both { get; set; } = new List<UInt32>();

        [DataMember]
        public List<UInt32> Rx { get; set; } = new List<UInt32>();

        [DataMember]
        public List<UInt32> Tx { get; set; } = new List<UInt32>();

    }
}
