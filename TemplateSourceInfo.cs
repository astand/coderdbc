using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CoderDbc
{
    public static class TemplateSourceInfo
    {
        public static readonly string HeadText = @"
";
        public static readonly string CPPGuardOpen = @"
#ifdef __cplusplus
extern ""C"" {
#endif
";

        public static readonly string CPPGuardClose = @"
#ifdef __cplusplus
}
#endif
";

        public static readonly string GuardInclude = @"
#pragma once
";
    }
}
