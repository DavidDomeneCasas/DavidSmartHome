// Hardware: Arduino Uno (Sparkfun, RedBoard) & RF Link Transmitter - 434MHz (433.92MHz)
const byte emissor = 5;
byte tempsI[3] = {3, 23, 15}; // Set time: dia [1-7], hora [0-23], minutos [0-59] (Per evitar errors, s'ha d'escriure l'hora sense zeros al davant. Ex.: Sí->7 / No->07.)
byte temps[3] = {tempsI[0], tempsI[1], tempsI[2]};
unsigned long t_reinici = 604800000; // millisegons que té una setmana.
unsigned long t = millis() ;

void setup()
{
    pinMode(emissor, OUTPUT); // RF Link Transmitter - 434MHz (433.92MHz)
    pinMode(12, OUTPUT); digitalWrite(12, HIGH); // Reset del hardware.
    
    t_reinici += 11000; // Correcció de temps per imprecició del rellotge del hardwar.
}

void loop()
{
  cronosHardware();
}

void cronosPersianes()
{
    // Laborables
    if (temps[0] < 6 && temps[1] == 7 && temps[2] == 0) persianes(0b111111, 4); // Pre-Pujada
    if (temps[0] < 6 && temps[1] == 8 && temps[2] == 0) persianes(0b111111, 1); // Pujada
    // Festius
    if (temps[0] >= 6 && temps[1] == 7 && temps[2] == 0) persianes(0b110000, 4); // Pre-Pujada
    if (temps[0] >= 6 && temps[1] == 8 && temps[2] == 0) persianes(0b110000, 1); // Pujada
    if (temps[0] >= 6 && temps[1] == 9 && temps[2] == 0) persianes(0b000011, 4); // Pre-Pujada
    if (temps[0] >= 6 && temps[1] == 10 && temps[2] == 0) persianes(0b000011, 1); // Pujada
    if (temps[0] >= 6 && temps[1] == 13 && temps[2] == 0) persianes(0b001100, 4); // Pre-Pujada
    if (temps[0] >= 6 && temps[1] == 13 && temps[2] == 15) persianes(0b001100, 1); // Pujada
    // Tots els dies
    if (temps[1] ==  18 && temps[2] == 0) persianes(0b111111, 3); // Baixada diaria

}

void persianes(byte persianes, short instruccio)
{
  if (persianes & 0b100000) accio(1,instruccio);
  if (persianes & 0b010000) accio(2,instruccio);
  if (persianes & 0b001000) accio(3,instruccio);
  if (persianes & 0b000100) accio(4,instruccio);
  if (persianes & 0b000010) accio(5,instruccio);
  if (persianes & 0b000001) accio(6,instruccio);

}

void accio(short persiana, short instruccio)
{
   if (instruccio == 4)
   {
      emissioDeRadio(persiana, 1);
      delay (2500) ;
      emissioDeRadio(persiana, 2);
   }
   else
   {
      emissioDeRadio(persiana, instruccio);
   } 
}

void emissioDeRadio(byte persiana, byte instruccio) // Codi per transmetre instruccions a les persianes (1 = pujar, 2 = aturar, 3 = baixar)
{ 
    bool b[66];
    b[0]=0, b[1]=1, b[2]=0, b[3]=1, b[4]=0, b[5]=1, b[6]=0, b[7]=1, b[8]=0, b[9]=1, b[10]=1, b[11]=1;
    switch(persiana)
    {
        case 1: switch(instruccio)
        {
            case 1: b[12]=0,b[13]=1,b[14]=1,b[15]=0,b[16]=0,b[17]=1,b[18]=1,b[19]=1,b[20]=1,b[21]=1,b[22]=1,b[23]=1,b[24]=1,b[25]=1,b[26]=0,b[27]=0,b[28]=1,b[29]=1,b[30]=1,b[31]=1,b[32]=0,b[33]=1,b[34]=0,b[35]=1,b[36]=0,b[37]=0,b[38]=0,b[39]=1,b[40]=0,b[41]=1,b[42]=1,b[43]=0,b[44]=1,b[45]=1,b[46]=1,b[47]=0,b[48]=1,b[49]=1,b[50]=1,b[51]=1,b[52]=1,b[53]=0,b[54]=0,b[55]=1,b[56]=1,b[57]=1,b[58]=1,b[59]=1,b[60]=0,b[61]=1,b[62]=1,b[63]=0,b[64]=1,b[65]=0;
                    break;
            case 2: b[12]=1,b[13]=0,b[14]=0,b[15]=1,b[16]=0,b[17]=0,b[18]=1,b[19]=1,b[20]=1,b[21]=1,b[22]=1,b[23]=1,b[24]=1,b[25]=1,b[26]=0,b[27]=0,b[28]=1,b[29]=1,b[30]=1,b[31]=1,b[32]=0,b[33]=1,b[34]=0,b[35]=1,b[36]=0,b[37]=0,b[38]=0,b[39]=1,b[40]=0,b[41]=1,b[42]=1,b[43]=0,b[44]=1,b[45]=1,b[46]=1,b[47]=0,b[48]=1,b[49]=1,b[50]=1,b[51]=1,b[52]=1,b[53]=0,b[54]=0,b[55]=1,b[56]=1,b[57]=1,b[58]=1,b[59]=1,b[60]=1,b[61]=0,b[62]=0,b[63]=1,b[64]=1,b[65]=0;
                    break;
            case 3: b[12]=1,b[13]=1,b[14]=0,b[15]=1,b[16]=1,b[17]=1,b[18]=0,b[19]=1,b[20]=1,b[21]=1,b[22]=1,b[23]=1,b[24]=1,b[25]=1,b[26]=0,b[27]=0,b[28]=1,b[29]=1,b[30]=1,b[31]=1,b[32]=0,b[33]=1,b[34]=0,b[35]=1,b[36]=0,b[37]=0,b[38]=0,b[39]=1,b[40]=0,b[41]=1,b[42]=1,b[43]=0,b[44]=1,b[45]=1,b[46]=1,b[47]=0,b[48]=1,b[49]=1,b[50]=1,b[51]=1,b[52]=1,b[53]=0,b[54]=0,b[55]=1,b[56]=1,b[57]=1,b[58]=1,b[59]=1,b[60]=1,b[61]=1,b[62]=0,b[63]=1,b[64]=1,b[65]=0;
                    break;
        }
        break;
        case 2: switch(instruccio)
        {
            case 1: b[12]=0,b[13]=1,b[14]=1,b[15]=0,b[16]=1,b[17]=0,b[18]=1,b[19]=1,b[20]=0,b[21]=0,b[22]=0,b[23]=0,b[24]=1,b[25]=1,b[26]=1,b[27]=1,b[28]=0,b[29]=1,b[30]=1,b[31]=1,b[32]=1,b[33]=0,b[34]=1,b[35]=1,b[36]=0,b[37]=0,b[38]=0,b[39]=0,b[40]=1,b[41]=1,b[42]=1,b[43]=0,b[44]=1,b[45]=1,b[46]=1,b[47]=0,b[48]=1,b[49]=1,b[50]=1,b[51]=1,b[52]=1,b[53]=0,b[54]=0,b[55]=1,b[56]=1,b[57]=1,b[58]=1,b[59]=1,b[60]=0,b[61]=1,b[62]=1,b[63]=0,b[64]=1,b[65]=0;
                    break;
            case 2: b[12]=1,b[13]=0,b[14]=0,b[15]=1,b[16]=1,b[17]=1,b[18]=0,b[19]=1,b[20]=0,b[21]=0,b[22]=0,b[23]=0,b[24]=1,b[25]=1,b[26]=1,b[27]=1,b[28]=0,b[29]=1,b[30]=1,b[31]=1,b[32]=1,b[33]=0,b[34]=1,b[35]=1,b[36]=0,b[37]=0,b[38]=0,b[39]=0,b[40]=1,b[41]=1,b[42]=1,b[43]=0,b[44]=1,b[45]=1,b[46]=1,b[47]=0,b[48]=1,b[49]=1,b[50]=1,b[51]=1,b[52]=1,b[53]=0,b[54]=0,b[55]=1,b[56]=1,b[57]=1,b[58]=1,b[59]=1,b[60]=1,b[61]=0,b[62]=0,b[63]=1,b[64]=1,b[65]=0;
                    break;
            case 3: b[12]=1,b[13]=1,b[14]=0,b[15]=1,b[16]=0,b[17]=1,b[18]=0,b[19]=1,b[20]=0,b[21]=0,b[22]=0,b[23]=0,b[24]=1,b[25]=1,b[26]=1,b[27]=1,b[28]=0,b[29]=1,b[30]=1,b[31]=1,b[32]=1,b[33]=0,b[34]=1,b[35]=1,b[36]=0,b[37]=0,b[38]=0,b[39]=0,b[40]=1,b[41]=1,b[42]=1,b[43]=0,b[44]=1,b[45]=1,b[46]=1,b[47]=0,b[48]=1,b[49]=1,b[50]=1,b[51]=1,b[52]=1,b[53]=0,b[54]=0,b[55]=1,b[56]=1,b[57]=1,b[58]=1,b[59]=1,b[60]=1,b[61]=1,b[62]=0,b[63]=1,b[64]=1,b[65]=0;
                    break;
        }
        break;
        case 3: switch(instruccio)
        {
            case 1: b[12]=0,b[13]=1,b[14]=1,b[15]=0,b[16]=1,b[17]=1,b[18]=1,b[19]=1,b[20]=1,b[21]=1,b[22]=1,b[23]=1,b[24]=1,b[25]=1,b[26]=1,b[27]=1,b[28]=1,b[29]=1,b[30]=1,b[31]=1,b[32]=0,b[33]=1,b[34]=1,b[35]=0,b[36]=1,b[37]=0,b[38]=1,b[39]=0,b[40]=1,b[41]=0,b[42]=1,b[43]=1,b[44]=1,b[45]=0,b[46]=1,b[47]=1,b[48]=1,b[49]=0,b[50]=1,b[51]=1,b[52]=0,b[53]=1,b[54]=1,b[55]=1,b[56]=1,b[57]=1,b[58]=1,b[59]=1,b[60]=1,b[61]=1,b[62]=1,b[63]=1,b[64]=1,b[65]=1;
                    break;
            case 2: b[12]=1,b[13]=0,b[14]=0,b[15]=1,b[16]=1,b[17]=1,b[18]=1,b[19]=1,b[20]=1,b[21]=1,b[22]=1,b[23]=1,b[24]=1,b[25]=1,b[26]=1,b[27]=1,b[28]=1,b[29]=1,b[30]=1,b[31]=1,b[32]=0,b[33]=1,b[34]=1,b[35]=0,b[36]=1,b[37]=0,b[38]=1,b[39]=0,b[40]=1,b[41]=0,b[42]=1,b[43]=1,b[44]=1,b[45]=0,b[46]=1,b[47]=1,b[48]=1,b[49]=0,b[50]=1,b[51]=1,b[52]=0,b[53]=1,b[54]=1,b[55]=1,b[56]=1,b[57]=1,b[58]=1,b[59]=1,b[60]=1,b[61]=1,b[62]=1,b[63]=1,b[64]=1,b[65]=1;
                    break;
            case 3: b[12]=1,b[13]=1,b[14]=0,b[15]=1,b[16]=1,b[17]=1,b[18]=1,b[19]=1,b[20]=1,b[21]=1,b[22]=1,b[23]=1,b[24]=1,b[25]=1,b[26]=1,b[27]=1,b[28]=1,b[29]=1,b[30]=1,b[31]=1,b[32]=0,b[33]=1,b[34]=1,b[35]=0,b[36]=1,b[37]=0,b[38]=1,b[39]=0,b[40]=1,b[41]=0,b[42]=1,b[43]=1,b[44]=1,b[45]=0,b[46]=1,b[47]=1,b[48]=1,b[49]=0,b[50]=1,b[51]=1,b[52]=0,b[53]=1,b[54]=1,b[55]=1,b[56]=1,b[57]=1,b[58]=1,b[59]=1,b[60]=1,b[61]=1,b[62]=1,b[63]=1,b[64]=1,b[65]=1;
                    break;
        }
        break;
        case 4: switch(instruccio)
        {
            case 1: b[12]=0,b[13]=1,b[14]=1,b[15]=0,b[16]=1,b[17]=1,b[18]=0,b[19]=1,b[20]=1,b[21]=1,b[22]=1,b[23]=1,b[24]=0,b[25]=1,b[26]=1,b[27]=0,b[28]=1,b[29]=1,b[30]=1,b[31]=1,b[32]=0,b[33]=0,b[34]=1,b[35]=1,b[36]=0,b[37]=0,b[38]=0,b[39]=0,b[40]=0,b[41]=1,b[42]=0,b[43]=1,b[44]=0,b[45]=0,b[46]=0,b[47]=1,b[48]=1,b[49]=1,b[50]=1,b[51]=1,b[52]=1,b[53]=0,b[54]=0,b[55]=1,b[56]=1,b[57]=0,b[58]=0,b[59]=1,b[60]=0,b[61]=1,b[62]=1,b[63]=0,b[64]=1,b[65]=0;
                    break;
            case 2: b[12]=1,b[13]=0,b[14]=0,b[15]=1,b[16]=1,b[17]=0,b[18]=0,b[19]=1,b[20]=1,b[21]=1,b[22]=1,b[23]=1,b[24]=0,b[25]=1,b[26]=1,b[27]=0,b[28]=1,b[29]=1,b[30]=1,b[31]=1,b[32]=0,b[33]=0,b[34]=1,b[35]=1,b[36]=0,b[37]=0,b[38]=0,b[39]=0,b[40]=0,b[41]=1,b[42]=0,b[43]=1,b[44]=0,b[45]=0,b[46]=0,b[47]=1,b[48]=1,b[49]=1,b[50]=1,b[51]=1,b[52]=1,b[53]=0,b[54]=0,b[55]=1,b[56]=1,b[57]=0,b[58]=0,b[59]=1,b[60]=1,b[61]=0,b[62]=0,b[63]=1,b[64]=1,b[65]=0;
                    break;
            case 3: b[12]=1,b[13]=1,b[14]=0,b[15]=1,b[16]=0,b[17]=0,b[18]=0,b[19]=1,b[20]=1,b[21]=1,b[22]=1,b[23]=1,b[24]=0,b[25]=1,b[26]=1,b[27]=0,b[28]=1,b[29]=1,b[30]=1,b[31]=1,b[32]=0,b[33]=0,b[34]=1,b[35]=1,b[36]=0,b[37]=0,b[38]=0,b[39]=0,b[40]=0,b[41]=1,b[42]=0,b[43]=1,b[44]=0,b[45]=0,b[46]=0,b[47]=1,b[48]=1,b[49]=1,b[50]=1,b[51]=1,b[52]=1,b[53]=0,b[54]=0,b[55]=1,b[56]=1,b[57]=0,b[58]=0,b[59]=1,b[60]=1,b[61]=1,b[62]=0,b[63]=1,b[64]=1,b[65]=0;
                    break;
        }
        break;
        case 5: switch(instruccio)
        {
            case 1: b[12]=0,b[13]=1,b[14]=1,b[15]=0,b[16]=0,b[17]=0,b[18]=1,b[19]=1,b[20]=1,b[21]=0,b[22]=0,b[23]=1,b[24]=0,b[25]=1,b[26]=0,b[27]=0,b[28]=1,b[29]=1,b[30]=1,b[31]=1,b[32]=1,b[33]=1,b[34]=1,b[35]=0,b[36]=0,b[37]=1,b[38]=0,b[39]=1,b[40]=0,b[41]=1,b[42]=1,b[43]=1,b[44]=0,b[45]=0,b[46]=0,b[47]=1,b[48]=1,b[49]=1,b[50]=1,b[51]=1,b[52]=1,b[53]=0,b[54]=0,b[55]=1,b[56]=1,b[57]=0,b[58]=0,b[59]=1,b[60]=0,b[61]=1,b[62]=1,b[63]=0,b[64]=1,b[65]=0;
                    break;
            case 2: b[12]=1,b[13]=0,b[14]=0,b[15]=1,b[16]=0,b[17]=1,b[18]=0,b[19]=1,b[20]=1,b[21]=0,b[22]=0,b[23]=1,b[24]=0,b[25]=1,b[26]=0,b[27]=0,b[28]=1,b[29]=1,b[30]=1,b[31]=1,b[32]=1,b[33]=1,b[34]=1,b[35]=0,b[36]=0,b[37]=1,b[38]=0,b[39]=1,b[40]=0,b[41]=1,b[42]=1,b[43]=1,b[44]=0,b[45]=0,b[46]=0,b[47]=1,b[48]=1,b[49]=1,b[50]=1,b[51]=1,b[52]=1,b[53]=0,b[54]=0,b[55]=1,b[56]=1,b[57]=0,b[58]=0,b[59]=1,b[60]=1,b[61]=0,b[62]=0,b[63]=1,b[64]=1,b[65]=0;
                    break;
            case 3: b[12]=1,b[13]=1,b[14]=0,b[15]=1,b[16]=1,b[17]=0,b[18]=0,b[19]=1,b[20]=1,b[21]=0,b[22]=0,b[23]=1,b[24]=0,b[25]=1,b[26]=0,b[27]=0,b[28]=1,b[29]=1,b[30]=1,b[31]=1,b[32]=1,b[33]=1,b[34]=1,b[35]=0,b[36]=0,b[37]=1,b[38]=0,b[39]=1,b[40]=0,b[41]=1,b[42]=1,b[43]=1,b[44]=0,b[45]=0,b[46]=0,b[47]=1,b[48]=1,b[49]=1,b[50]=1,b[51]=1,b[52]=1,b[53]=0,b[54]=0,b[55]=1,b[56]=1,b[57]=0,b[58]=0,b[59]=1,b[60]=1,b[61]=1,b[62]=0,b[63]=1,b[64]=1,b[65]=0;
                    break;
        }
        break;
        case 6: switch(instruccio)
        {
            case 1: b[12]=0,b[13]=1,b[14]=1,b[15]=0,b[16]=1,b[17]=0,b[18]=0,b[19]=1,b[20]=1,b[21]=1,b[22]=0,b[23]=0,b[24]=0,b[25]=0,b[26]=1,b[27]=0,b[28]=1,b[29]=1,b[30]=1,b[31]=1,b[32]=0,b[33]=0,b[34]=1,b[35]=1,b[36]=1,b[37]=0,b[38]=1,b[39]=1,b[40]=1,b[41]=0,b[42]=1,b[43]=1,b[44]=0,b[45]=0,b[46]=0,b[47]=1,b[48]=1,b[49]=1,b[50]=1,b[51]=1,b[52]=1,b[53]=0,b[54]=0,b[55]=1,b[56]=1,b[57]=0,b[58]=0,b[59]=1,b[60]=0,b[61]=1,b[62]=1,b[63]=0,b[64]=1,b[65]=0;
                    break;
            case 2: b[12]=1,b[13]=0,b[14]=0,b[15]=1,b[16]=1,b[17]=1,b[18]=1,b[19]=0,b[20]=1,b[21]=1,b[22]=0,b[23]=0,b[24]=0,b[25]=0,b[26]=1,b[27]=0,b[28]=1,b[29]=1,b[30]=1,b[31]=1,b[32]=0,b[33]=0,b[34]=1,b[35]=1,b[36]=1,b[37]=0,b[38]=1,b[39]=1,b[40]=1,b[41]=0,b[42]=1,b[43]=1,b[44]=0,b[45]=0,b[46]=0,b[47]=1,b[48]=1,b[49]=1,b[50]=1,b[51]=1,b[52]=1,b[53]=0,b[54]=0,b[55]=1,b[56]=1,b[57]=0,b[58]=0,b[59]=1,b[60]=1,b[61]=0,b[62]=0,b[63]=1,b[64]=1,b[65]=0;
                    break;
            case 3: b[12]=1,b[13]=1,b[14]=0,b[15]=1,b[16]=0,b[17]=0,b[18]=1,b[19]=0,b[20]=1,b[21]=1,b[22]=0,b[23]=0,b[24]=0,b[25]=0,b[26]=1,b[27]=0,b[28]=1,b[29]=1,b[30]=1,b[31]=1,b[32]=0,b[33]=0,b[34]=1,b[35]=1,b[36]=1,b[37]=0,b[38]=1,b[39]=1,b[40]=1,b[41]=0,b[42]=1,b[43]=1,b[44]=0,b[45]=0,b[46]=0,b[47]=1,b[48]=1,b[49]=1,b[50]=1,b[51]=1,b[52]=1,b[53]=0,b[54]=0,b[55]=1,b[56]=1,b[57]=0,b[58]=0,b[59]=1,b[60]=1,b[61]=1,b[62]=0,b[63]=1,b[64]=1,b[65]=0;
                    break;
         }
         break;
    }
      for (short i = 0; i < 48; i ++)
      {
          digitalWrite(emissor, HIGH); delayMicroseconds(400);
          digitalWrite(emissor, LOW); delayMicroseconds(400);
      }
      delayMicroseconds(3600);
      for (short i = 0; i <= 65; i ++)
      {
          if (b[i] == 0)
          {
              digitalWrite(emissor, HIGH); delayMicroseconds(400);
              digitalWrite(emissor, LOW); delayMicroseconds(800);
          }
          else
          {
              digitalWrite(emissor, HIGH); delayMicroseconds(800);
              digitalWrite(emissor, LOW); delayMicroseconds(400);
          }
      }
      digitalWrite (emissor, LOW);
      delay(800);
}

void cronosHardware()
{
  if (millis() > t + 60000) 
  {
     if (temps[2] == (byte) 59)
     {
        temps[2] = 0;
        if (temps[1] == (byte) 23)
        {
            temps[1] = 0;
            if (temps[0] == (byte) 7) temps[0] = 1;
            else temps[0] ++ ;
        } 
        else temps[1] ++ ;
     }
     else temps[2] ++ ;
     t += 60000 ;
     cronosPersianes();
  }
  if ( millis() >= t_reinici) digitalWrite(12, LOW); // Reset hardware.
}
