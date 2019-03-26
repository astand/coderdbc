using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace CoderDbc
{
    [DataContract]
    public class PackUnpackSettings
    {
        // this setting determines if the special CAN typedef struct will be used in pack/unpack
        // and global receive function
        [DataMember]
        public int UseCANFrame { get; set; } = 0;

        // this settings will put the calling FMon_*drvname* functions after the frame received
        // and put the fmon_*drvname*.h file with all the prototypes of monitor functions
        // and the user must define all these functions
        [DataMember]
        public int UseMonitors { get; set; } = 0;

        // when this option is set to 1 then all the signals with unsigned types and with size less then 8 bytes
        // will be declared as bit-fields
        [DataMember]
        public int UseBitField { get; set; } = 0;
    }


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
        public PackUnpackSettings Code { get; set; } = new PackUnpackSettings();

        [DataMember]
        public List<UInt32> Both { get; set; } = new List<UInt32>();

        [DataMember]
        public List<UInt32> Rx { get; set; } = new List<UInt32>();

        [DataMember]
        public List<UInt32> Tx { get; set; } = new List<UInt32>();

        [DataMember]
        public List<UInt32> NoCode { get; set; } = new List<UInt32>();
    }
}
