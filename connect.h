#define data P3
#define statu1 P0^1
#define statu2 P0^2
#define statu3 P0^3
#define statu4 P0^4
#define statu5 P0^5

void TimeToDo()
{
  if(!statu1)
  {
    if(!statu2 && !statu3 && !statu4 && !statu5)
      PIDto[0] = data;
    if(!statu2 && !statu3 && !statu4 && statu5)
      PIDto[1] = data;
    if(!statu2 && !statu3 && statu4 && !statu5)
      PIDto[2] = data;
    if(!statu2 && !statu3 && statu4 && statu5)
      PIDto[3] = data;
    if(!statu2 && statu3 && !statu4 && !statu5)
      dja = data;
  }
  else
  {
    if(!statu2 && !statu3 && !statu4 && !statu5)
      data = MilesToSend[0][0];
    if(!statu2 && !statu3 && !statu4 && statu5)
      data = MilesToSend[0][1];
    if(!statu2 && !statu3 && statu4 && !statu5)
      data = MilesToSend[1][0];
    if(!statu2 && !statu3 && statu4 && statu5)
      data = MilesToSend[1][1];
    if(!statu2 && statu3 && !statu4 && !statu5)
      data = MilesToSend[2][0];
    if(!statu2 && statu3 && !statu4 && statu5)
      data = MilesToSend[2][1];
    if(!statu2 && statu3 && statu4 && !statu5)
      data = MilesToSend[3][0];
    if(!statu2 && statu3 && statu4 && statu5)
      data = MilesToSend[3][1];
    if(statu2 && !statu3 && !statu4 && !statu5)
      data = pos[0][0];
    if(statu2 && !statu3 && !statu4 && statu5)
      data = pos[0][1];
    if(statu2 && !statu3 && statu4 && !statu5)
      data = pos[1][0];
    if(statu2 && !statu3 && statu4 && statu5)
      data = pos[1][1];
    if(statu2 && statu3 && !statu4 && statu5)
      data = agl[0][0];
    if(statu2 && statu3 && !statu4 && !statu5)
      data = agl[0][1];
    if(statu2 && statu3 && statu4 && statu5)
      data = agl[1][0];
    if(statu2 && statu3 && statu4 && !statu5)
      data = agl[1][1];
  }
}
