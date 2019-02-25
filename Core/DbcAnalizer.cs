using CoderDbc.Models;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;

namespace CoderDbc.Core
{
    public class DbcAnalizer
    {
        public List<MessageDescriptor> Messages { get; set; } = new List<MessageDescriptor>();

        public DbcAnalizer()
        {
        }

        public void TrimDbcRawStream(StringReader reader)
        {
            var line = String.Empty;
            MessageDescriptor msgDesc = null;

            while ((line = reader.ReadLine()) != null)
            {
                if (line.StartsWith("BO_ "))
                {
                    if (msgDesc != null)
                    {
                        // this means that new message was met and previous message needs to be added to list
                        msgDesc.AddSignals(msgDesc.Signals.OrderBy(o => o.StartBit).ToList());
                        Messages.Add(msgDesc);
                    }

                    msgDesc = new MessageDescriptor();

                    if (!msgDesc.ParseVectorDbcLine(line))
                    {
                        // bad unparsing. clear message reference
                        msgDesc = null;
                    }
                }

                if (regSigStart.IsMatch(line) && (msgDesc != null))
                {
                    var sig = new SignalBitsDesc();
                    sig.ParseFromVectorDbcString(line);
                    msgDesc.Signals.Add(sig);
                }
                else if (line.StartsWith("BA_ "))
                {
                    // try parse this section for getting cycle time
                    var bastr = new AttrDescriptor();

                    if (bastr.ParseBA_(line) == true)
                    {
                        if (ba_.Where(b => b.MsgId == bastr.MsgId).FirstOrDefault() == null)
                        {
                            // there is no this message in collection yet
                            ba_.Add(bastr);
                        }
                    }
                }

                if (line.StartsWith("CM_ ") || commenter.IsCollectingData)
                {
                    if (commenter.PassString(line) == true)
                    {
                        if (commenter.Info.Type == CommentType.MessageComment)
                        {
                            var msg = Messages.Where(m => m.MessageId == commenter.Info.MsgId).FirstOrDefault();

                            if (msg != null)
                            {
                                // appropriate message was found
                                msg.CommentText = commenter.Info.Text;
                            }
                        }
                        else if (commenter.Info.Type == CommentType.SignalComment)
                        {
                            var msg = Messages.Where(m => m.MessageId == commenter.Info.MsgId).FirstOrDefault();

                            if (msg != null)
                            {
                                // appropriate message was found
                                var sig = msg.Signals.Where(s => s.FieldName == commenter.Info.SigName).FirstOrDefault();

                                if (sig != null)
                                {
                                    sig.CommentText = commenter.Info.Text;

                                    if (IsRollingCounterCodeAvailalbe && sig.CommentText.Contains(RollingCounterMatch))
                                    {
                                        if (msg.RollSig == null)
                                            msg.RollSig = sig;
                                    }
                                    else if (IsChecksumMatchCodeAvailable && sig.CommentText.Contains(ChecksumMatch))
                                    {
                                        if (msg.CsmSig == null)
                                        {
                                            msg.CsmType = "kCRCUndefined";

                                            if (sig.CommentText.Contains("SAEJ1850"))
                                            {
                                                msg.CsmType = "kSAEJ1850";
                                            }
                                            else if (sig.CommentText.Contains("XOR8"))
                                            {
                                                msg.CsmType = "kXOR8";
                                            }

                                            msg.CsmSig = sig;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                else if (line.StartsWith("VAL_ "))
                {
                    valuator.PassString(line);
                    var msg = Messages.Where(m => m.MessageId == valuator.MsgId).FirstOrDefault();

                    if (msg != null)
                    {
                        // appropriate message was found
                        var sig = msg.Signals.Where(s => s.FieldName == valuator.SigName).FirstOrDefault();

                        if (sig != null)
                        {
                            sig.ValueText = valuator.Text;
                        }
                    }
                }

                Messages = Messages.OrderBy(m => m.MessageId).ToList();
            }

            if (msgDesc != null)
            {
                msgDesc.Signals = msgDesc.Signals.OrderBy(o => o.StartBit).ToList();
                Messages.Add(msgDesc);
            }

            foreach (var ba in ba_)
            {
                // update all the messages with parsed succesfully cycle time
                var msg = Messages.Where(d => d.MessageId == ba.MsgId).FirstOrDefault();

                if (msg != null)
                {
                    msg.CycTime = ba.CycTime;
                }
            }
        }

        private List<AttrDescriptor> ba_ = new List<AttrDescriptor>();

        Commenter commenter = new Commenter();
        ValParser valuator = new ValParser();
        Regex regSigStart = new Regex(@"(^\s+SG_)");
        public string RollingCounterMatch { get; set; } = "Rolling Counter ";
        public string ChecksumMatch { get; set; } = "Checksum ";
        public bool IsRollingCounterCodeAvailalbe { get; set; } = false;
        public bool IsChecksumMatchCodeAvailable { get; set; } = false;
    }
}
