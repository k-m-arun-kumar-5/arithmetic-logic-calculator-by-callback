/* ********************************************************************
FILE                   : CALLBACK.c

PROGRAM DESCRIPTION    : demo of callback with arithmetic operation of addition, subtraction, multipliation and division and
                         bit operation of AND, OR, XOR, Complement

AUTHOR                :  K.M. Arun Kumar alias Arunkumar Murugeswaran

KNOWN BUGS            :

NOTE                  :  Compiled and Tested in Dev-C++ on Windows 7 (32 bit) Desktop OS.

CHANGE LOGS           :

*****************************************************************************/
#include <stdio.h>
typedef void *(*callback)( const void *const, const void *const );
typedef void *(*register_callback) ( const void *const, const void *const, const char );

void *switch_callback_reg( const void *const, const void *const, const char );
void *register_callback_func(const void *const,  const void *const, const char arithmetic, register_callback );

void *arith_callback_reg( const void *const ptr_oper1_num,  const void *const ptr_oper2_num, const char arithmetic_oper);
void *logic_callback_reg( const void *const ptr_oper1_num,  const void *const ptr_oper2_num, const char logic_oper);

void *add_arith( const void *const ptr_oper1_num,  const void *const ptr_oper2_num);
void *sub_arith( const void *const ptr_oper1_num,  const void *const ptr_oper2_num);
void *mul_arith( const void *const ptr_oper1_num,  const void *const ptr_oper2_num);
void *div_arith( const void *const ptr_oper1_num,  const void *const ptr_oper2_num);
void *mod_arith( const void *const ptr_oper1_num,  const void *const ptr_oper2_num);

void *and_logic(const void *const ptr_oper1_num,  const void *const ptr_oper2_num);
void *or_logic(const void *const ptr_oper1_num,  const void *const ptr_oper2_num);
void *xor_logic(const void *const ptr_oper1_num,  const void *const ptr_oper2_num);
void *comp1_logic(const void *const ptr_oper1_num,  const void *const ptr_oper2_num);
void *comp2_logic(const void *const ptr_oper1_num,  const void *const ptr_oper2_num);

void *voidptr_ans_num  =NULL;
int oper1_num, oper2_num, ans_num;
char oper;
int main()
{
   int *ptr_ans_num;
   char continue_flag = 'y', type_oper = 'a';
    
	
   do{	
   printf("\n Enter oper1_num = ");
   scanf("%d", &oper1_num);
   printf("\n Enter oper2_num = ");
   scanf("%d", &oper2_num);
   printf("\n MENU for oper: 'a' arith , 'l' logic ");
   printf("\n Enter oper = ");
   scanf("%1s", &type_oper);
   ptr_ans_num = (int *)switch_callback_reg(&oper1_num, &oper2_num,type_oper);
   if(ptr_ans_num)
   {
      ans_num = *ptr_ans_num;
	  switch(type_oper)
	  {
		  case 'a':
	     printf("\n %d '%c' %d = %d", oper1_num,oper,oper2_num, ans_num );
			 break;
		 case 'l':
		printf("\n 0x%X '%c' 0x%X = 0x%X", oper1_num,oper,oper2_num, ans_num );
	    break;
      }
      }
	  printf("\n Continue - type 'y' or 'Y', any other char to exit");
	  printf("\n Enter : ");
	  scanf("%1s", &continue_flag);
   } while (continue_flag == 'y' || continue_flag == 'Y');
   return 0;
}
void *switch_callback_reg( const void *const ptr_oper1_num,  const void *const ptr_oper2_num, const char oper_type)
{
	register_callback callback_reg;
	switch(oper_type)
	{
		case 'a':
		 printf("\n MENU : '+' addition, '-' subtraction, '*' mul , '/' div and '%' Mod" );
	 printf("\n Enter arith oper : ");
		 scanf("%1s", &oper);
		 callback_reg = arith_callback_reg;
		 break;
		 case 'l':
		 printf("\n MENU : '&' AND, '|' OR, '^' XOR , '~' comp1, '@' comp2 " );
	 printf("\n Enter logic oper : ");
		 scanf("%1s", &oper);
		 callback_reg = logic_callback_reg;
		 break;
		default:
		  callback_reg = NULL;
	}
	if(callback_reg)
	  return( register_callback_func(ptr_oper1_num,ptr_oper2_num, oper, callback_reg));
    else
	return NULL;
}

void *register_callback_func(const void *const ptr_oper1_num, const void *const ptr_oper2_num, const char arithmetic_oper, register_callback callback_func )
{
	return callback_func(ptr_oper1_num,ptr_oper2_num,arithmetic_oper);
}

void *arith_callback_reg( const void *const ptr_oper1_num,  const void *const ptr_oper2_num, const char arithmetic_oper)
{
	callback arith_callback;
	switch(arithmetic_oper)
	{
		case '+':
		  arith_callback = add_arith;
		  break;
		case '-':
	      arith_callback = sub_arith;
		  break;
	    case '*':
	      arith_callback = mul_arith;
		  break;
	   case '/':
	     arith_callback = div_arith;
		  break;
		case '%':
	      arith_callback = mod_arith;
		  break;
	default:
	  arith_callback =  NULL;
	}
	if(arith_callback)
	   return arith_callback(ptr_oper1_num,ptr_oper2_num);
    else
     return NULL;
}

void *logic_callback_reg( const void *const ptr_oper1_num,  const void *const ptr_oper2_num, const char logic_oper)
{
	callback logic_callback;
	switch(logic_oper)
	{
		case '&':
		  logic_callback = and_logic;
		  break;
		case '|':
	      logic_callback = or_logic;
		  break;
	    case '^':
	      logic_callback = xor_logic;
		  break;
	   case '~':
	      logic_callback = comp1_logic;
		  break;
      case '@':
	      logic_callback = comp2_logic;
		  break;
	   default:
	     logic_callback =  NULL;
	}
	if(logic_callback)
	   return logic_callback(ptr_oper1_num,ptr_oper2_num);
    else
     return NULL;
}

void *add_arith( const void *const ptr_oper1_num,  const void *const ptr_oper2_num)
{
	int oper1_num, oper2_num ;
	oper1_num = *(int *)ptr_oper1_num;
	oper2_num = *(int *)ptr_oper2_num;
	ans_num = oper1_num + oper2_num;
	return(&ans_num);

}
void *sub_arith( const void *const ptr_oper1_num,  const void *const ptr_oper2_num)
{
	int oper1_num, oper2_num ;
	oper1_num = *(int *)ptr_oper1_num;
	oper2_num = *(int *)ptr_oper2_num;
	ans_num = oper1_num - oper2_num;
	return(&ans_num);

}
void *mul_arith( const void *const ptr_oper1_num,  const void *const ptr_oper2_num)
{
	int oper1_num, oper2_num ;
	oper1_num = *(int *)ptr_oper1_num;
	oper2_num = *(int *)ptr_oper2_num;
	ans_num = oper1_num * oper2_num;
	return(&ans_num);

}
void *div_arith( const void *const ptr_oper1_num,  const void *const ptr_oper2_num)
{
	int oper1_num, oper2_num ;
	oper1_num = *(int *)ptr_oper1_num;
	oper2_num = *(int *)ptr_oper2_num;
	if(oper2_num == 0)
    {
		printf("\n ERR: divisor = 0");
		return NULL;
	}
	ans_num = oper1_num * oper2_num;
	return(&ans_num);

}
void *mod_arith( const void *const ptr_oper1_num,  const void *const ptr_oper2_num)
{
	int oper1_num, oper2_num ;
	oper1_num = *(int *)ptr_oper1_num;
	oper2_num = *(int *)ptr_oper2_num;
	if(oper2_num == 0)
    {
		printf("\n ERR: divisor = 0");
		return NULL;
	}
	ans_num = oper1_num % oper2_num;
	return(&ans_num);

}
void *and_logic(const void *const ptr_oper1_num,  const void *const ptr_oper2_num)
{
	int oper1_num, oper2_num ;
	oper1_num = *(int *)ptr_oper1_num;
	oper2_num = *(int *)ptr_oper2_num;
	ans_num = oper1_num & oper2_num;
	return(&ans_num);
}
void *or_logic(const void *const ptr_oper1_num,  const void *const ptr_oper2_num)
{
	int oper1_num, oper2_num ;
	oper1_num = *(int *)ptr_oper1_num;
	oper2_num = *(int *)ptr_oper2_num;
	ans_num = oper1_num | oper2_num;
	return(&ans_num);
}
void *xor_logic(const void *const ptr_oper1_num,  const void *const ptr_oper2_num)
{
	int oper1_num, oper2_num ;
	oper1_num = *(int *)ptr_oper1_num;
	oper2_num = *(int *)ptr_oper2_num;
	ans_num = oper1_num ^ oper2_num;
	return(&ans_num);
}
void *comp1_logic(const void *const ptr_oper1_num,  const void *const ptr_oper2_num)
{
	int oper1_num, oper2_num ;
	oper1_num = *(int *)ptr_oper1_num;
	ans_num = ~oper1_num;
	return(&ans_num);
}



void *comp2_logic(const void *const ptr_oper1_num,  const void *const ptr_oper2_num)
{
	int oper2_num ;
	oper2_num = *(int *)ptr_oper2_num;
	ans_num = ~oper2_num;
	return(&ans_num);
}

#ifdef EXAMPLE_CALLBACK

typedef void (*callback)(void);
void register_callback(callback ptr_reg_callback);
void my_callback(void)
{
    printf("inside my_callback\n");
}

int main(void)
{
    /* initialize function pointer to
    my_callback */
    callback ptr_my_callback=my_callback;
    printf("This is a program demonstrating function callback\n");
    /* register our callback function */
    register_callback(ptr_my_callback);
    printf("back inside main program\n");
    return 0;
}


/* registration goes here */
void register_callback(callback ptr_reg_callback)
{
    printf("inside register_callback\n");
    /* calling our callback function my_callback */
    (*ptr_reg_callback)();
}
#endif




