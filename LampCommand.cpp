
#include "LampCommand.h"


LampCommand::LampCommand(const char * command, int len): 
ctype(UNKN), clength(0), cvalue(0)
{
   if (command && (len > 0))
   {
      //type
      this->ctype = *command;
      //length
      if (len >= 3)
      {
         unsigned char l1 = command[1];
         unsigned char l2 = command[2];
         this->clength = l1 * 256 + l2;
         //value
         if (this->clength > 0 && len == this->clength + 3)
         {
            this->cvalue = new char[this->clength];
            const char * val = (command + 3);
            for (int i = 0; i < this->clength; i++)
            {
               this->cvalue[i] = val[i];
            }
         }
      }
   }
}

LampCommand::LCommand LampCommand::type() const
{
   return (LampCommand::LCommand)this->ctype;
}

unsigned short LampCommand::length() const
{
   return this->clength;
}

const char * LampCommand::value() const
{
   return this->cvalue;
}

