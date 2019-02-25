using CoderDbc.Models;
using System.Collections.Generic;
using System.Linq;

namespace CoderDbc.Core
{
    public class DbcSrcUtil_Bin : DbcSrcUtil_Common
    {
        public DbcSrcUtil_Bin()
        {
            utilName = "_binUtil";
        }

        protected override void GenerateSourceBody(List<MessageDescriptor> msgs, string utilName)
        {
            var orderMsgs = msgs.OrderBy(m => m.MessageId).ToList();
            FuncUtilName = utilName;
            writer.Clear();

            if (msgs.Count() > 0)
            {
                tree = FillTreeLevel(orderMsgs, 0, orderMsgs.Count);
                srcContent.end.AppendLine($"uint32_t {utilName}_Receive({utilName}_{rxSuff}_t* _m, const uint8_t* _d, uint32_t _id)");
                srcContent.end.AppendLine("{");
                srcContent.end.AppendLine(" uint32_t recid = 0;");
                srcContent.end.AppendLine(writer.WriteCode(tree, 1));
                srcContent.end.AppendLine(" return recid;");
                srcContent.end.AppendLine("}");
                srcContent.end.AppendLine();
            }
        }

        protected ConditionalTree FillTreeLevel(List<MessageDescriptor> list, int l, int h, bool started = false)
        {
            var ret = new ConditionalTree();
            var span = h - l;
            var lowhalf = span / 2;
            var highhalf = span - lowhalf;
            TreeStarted = started;

            if (h < 1)
            {
                return null;
            }

            if (!TreeStarted && h == 1)
            {
                ret.conditionalType = ConditionalType.Cond;
                var msg = list[l];
                ret.ConditionExpresion = "_id == " + msg.PrintMsgIDValue;
                ret.High = new ConditionalTree()
                {
                    conditionalType = ConditionalType.Express,
                    UtilCodeBody = $"recid = Unpack_{msg.MessageName}_{FuncUtilName}(" + @"&" + $"(_m->{msg.MessageName}), _d); " +
                                   $"_m->csm_bit = _m->{msg.MessageName}.mon1.checksum_error; _m->roll_bit = _m->{msg.MessageName}.mon1.roll_error;"
                };
                return ret;
            }

            if (span > 1)
            {
                ret.conditionalType = ConditionalType.Cond;

                if (lowhalf > 1)
                    ret.ConditionExpresion = "_id >= 0x" + list[l].MessageId.ToString("X") +
                                             "U && _id < 0x" + list[(l + lowhalf)].MessageId.ToString("X") + "U";
                else
                    ret.ConditionExpresion = "_id == " + list[l].PrintMsgIDValue;

                ret.High = FillTreeLevel(list, l, l + lowhalf, true);
                ret.Low = FillTreeLevel(list, l + lowhalf, h, true);
            }
            else
            {
                ret.conditionalType = ConditionalType.Express;
                var msg = list[l];
                ret.ConditionExpresion = "_id == " + msg.PrintMsgIDValue;
                ret.UtilCodeBody = $"recid = Unpack_{msg.MessageName}_{FuncUtilName}(" + @"&" + $"(_m->{msg.MessageName}), _d); ";
                ret.UtilCodeBody += $"_m->csm_bit = _m->{msg.MessageName}.mon1.checksum_error; _m->roll_bit = _m->{msg.MessageName}.mon1.roll_error;";
            }

            return ret;
        }

        public string FuncUtilName { get; set; }
        bool TreeStarted = false;
        ConditionalTree tree;
        ConditionalTreeCWriter writer = new ConditionalTreeCWriter();
    }
}
