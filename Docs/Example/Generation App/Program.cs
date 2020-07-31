using CoderDbc;
using CoderDbc.Core;
using CoderDbc.Models;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Reflection;

namespace DbcCoder
{
    class Program
    {
        static void Main(string[] args)
        {
            // Make string reader from DBC file
            StringReader dbcreader = new StringReader(File.ReadAllText(@"example.dbc"));
            // create DbcAnalyzer and perfrom parsing
            var analyzer = new DbcAnalizer();
            // Trim Dbc extracts all information about each message
            analyzer.TrimDbcRawStream(dbcreader);

            GenerationSettings gsett = new GenerationSettings()
            {
                NeedFrameCounting = false,

                // This option adds offset correction inside unpacking function
                NeedOffsetCalc = true,

                // Packed extension will placed in : "typedef {Packed} struct { ..."
                Packed = "",

                Code = new PackUnpackSettings()
                {

                    // Frame struct will be defined with bitfields (I don't like it)
                    UseBitField = 0,

                    // Pack/Unpack message will be intake a pointer on struct 
                    // that must be typedefed in user code scope and must contain 
                    // few obligatory data fields
                    UseCANFrame = 1,
                    // Using monitors adds additional filed in frame (fmon1) that helps
                    // to check if frame has bad checksum, rolling counter or frame stopped

                    // When monitors are on, be sure to do GetSystemTick() implementaion - 
                    // function that must return timer tick that will be stored in fmon1.last_cycle
                    // (see example code)
                    UseMonitors = 1
                },

                // These Frames will be added to RX struct in binUtil source files
                // This type of struct is expected in the global {drivername}_Receive() function
                Rx = new List<UInt32>() { 0x162, 0x164 },

                // These Frames will be added to TX struct in binUtil source files
                Tx = new List<UInt32>() { 0x111, 0x112 },

                // These Frames will be added to both TX and RX structs
                Both = new List<UInt32>() { 0x10, 0x30, 0x40 },

                // For these message IDs code won't be generated 
                // (nor for packing neither unpacking)
                NoCode = new List<UInt32>() { 387, 399, 512, 593, 608, 625, 640, 688, 790, 809, 832, 871, 872, 882,
                    896, 897, 899, 900, 903, 1017, 1024, 1040, 1064, 1065, 1066, 1078, 1156, 1157, 1168, 1170, 1191,
                    1265, 1280, 1281, 1282, 1292, 1301, 1307, 1312, 1313, 1314, 1315, 1316, 1317, 1318, 1319, 1322,
                    1338, 1342, 1345, 1349, 1350, 1351, 1353, 1356, 1360, 1362, 1363, 1365, 1366, 1367, 1369, 1370,
                    1371, 1378, 1379, 1393, 1395, 1397, 1407, 1411, 1412, 1414, 1415, 1419, 1425, 1427, 1434, 1437,
                    1440, 1441, 1456, 1472, 1479, 1490, 1491, 1492, 1530, 1531, 1532 },
            };

            // All messages must be marked by Direction value, before generation
            // This markers will be used by main generator to skip NoCode frames
            // by util generator to split messages on TX and RX structs.
            foreach (var msg in analyzer.Messages)
            {
                if (gsett.Rx.Contains(msg.MessageId)) msg.direction = Direction.Rx;
                if (gsett.Tx.Contains(msg.MessageId)) msg.direction = Direction.Tx;
                if (gsett.Both.Contains(msg.MessageId)) msg.direction = Direction.Both;
                if (gsett.NoCode.Contains(msg.MessageId)) msg.direction = Direction.NoCode;
            }

            // @DbcSourceCodeGenerator generates main C code with 
            // Message structs, signal conversion macros
            // Pack/Unpack functions
            // (see example code)
            var generator = new DbcSourceCodeGenerator() { CodeSett = gsett };

            generator.Generate(
                analyzer.Messages.Where<MessageDescriptor>(o => o.direction != Direction.NoCode).ToList(),  // Extracted by DbcAnalizer messages
                "gens_src",         // Directory where source code will be placed
                "coderEx",          // global Driver prefix
                "// Coder Example Main Files " // Any text that will be placed 
                                            // at the start or source files
                );

            // @DbcSrcUtil_Bin generates util C code with
            // struct of messages for TX action and RX action,
            // {drivername}_Receive() function, that could be used
            // as single function for receiving any frame from RX struct
            // (see example code)
            var binutilgen = new DbcSrcUtil_Bin() { CodeSett = gsett };
            binutilgen.Generate(
                analyzer.Messages,              // Extracted by DbcAnalizer messages
                "gens_src",                     // Directory where source code will be placed
                "coderEx",                 // global Driver prefix
                "// Coder Example Main Files "     // Any text that will be placed 
                                                // at the start of source files
                );

            // 1
            // After this code executed in directory @gens_src all driver
            // source files will be added. Pay attention to file read-only properies, 
            // i.e. next generation will fail, because rewriting these files is prohibited
            // Next list of files will be found:
            // coderex.c            - main C source file
            // coderex.h            - main C header file
            // coderex_binUtil.c    - util C source file 
            // coderex_binUtil.h    - util C header file

            // 2
            // As well next files (because of "UseMonitors = 1")
            // canmonitorutil.h     - header defines struct that used in fails monitoring
            //                        methods. Two functions must be implemented in user code
            //                        (GetCrcValueForArray, GetSystemTick)
            // fmon-coderex.h       - header contains FMon_* prototypes for functions 
            //                        that must be implemented in user code, these function
            //                        will only be called when related CAN message is unpacked

            // 3
            // File that is not generated but must be added is dbccodeconf.h
            // This file uses for next purposes:
            // - here __USE_{DRIVERNAME}__ must be defined, to enable auto RX, TX structs
            //   be created.
            // - In this file {__CoderDbcCanFrame_t__} typedef must be defined
            //   (necessary when UseCANFrame = 1 in other simple signatures will be generated

            // see example code with proper implementations.

            // PS Automatic checksum calculation supports only for 8 bit width value that placed in 
            // the last byte of frame payload, to put function calling generator must find
            // keyword in signal comment, also type of algorythm must be provided
        }
    }
}
