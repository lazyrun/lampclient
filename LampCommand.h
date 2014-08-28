#ifndef LAMPCOMMAND_H
#define LAMPCOMMAND_H

class LampCommand
{
public:
   enum LCommand
   {
      ON    = 0x12,
      OFF   = 0x13,
      COLOR = 0x20,
      UNKN  = 0xFF
   };

   LampCommand(const char * command = 0, int len = 0);
   LCommand type() const;
   unsigned short length() const;
   const char * value() const;

private:
   unsigned char ctype;
   unsigned short clength;
   char * cvalue;
};

#endif
