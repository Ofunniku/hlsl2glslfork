// Copyright (c) The HLSL2GLSLFork Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE.txt file.


#include "glslStruct.h"

std::string GlslStruct::getDecl() const
{
   std::stringstream out;

   out << "struct " << name << " {\n";

   for (std::vector<member>::const_iterator it = memberList.begin(); it != memberList.end(); it++) 
   {
      out << "    ";
      writeType (out, it->type, 0, it->precision);
      out << " " << it->name;

      if (it->arraySize > 0)
         out << "[" << it->arraySize << "]";

      out << ";\n";
   }

   out << "};\n";

   return out.str();
}
