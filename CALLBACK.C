/* ********************************************************************
FILE                   : CALLBACK.c

PROGRAM DESCRIPTION    : demo of callback function with arithmetic operation of addition, subtraction, multipliation and division and
                         bit operation of AND, OR, XOR, Complement

AUTHOR                :  K.M. Arun Kumar alias Arunkumar Murugeswaran

KNOWN BUGS            :

NOTE                  :  

CHANGE LOGS           :

*****************************************************************************/
#include <stdio.h>
#include <limits.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

typedef unsigned char uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;

typedef char int8_t;
typedef short int int16_t;
typedef int int32_t;
typedef long int64_t;

#define NULL_DATA_PTR                            ((void *)0)
#define NULL_CHAR                               ('\0')

#define STR_MAX_CHARS                            (7)

typedef enum { SUCCESS, FAILURE, FSM_OPERAND_1, FSM_OPERAND_2, FSM_NUM_OPER_TYPE, FSM_ARITH_OPER, FSM_LOGIC_OPER,
               FSM_NUM_OPER_RESULT, FSM_TO_CONTINUE} sys_status_t;

unsigned char system_fsm;

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

uint16_t Get_Validate_Input_Number(void *const int32_input_num_ptr, char *const input_str_ptr, const unsigned int input_str_max_chars, const int32_t valid_min_value, const int32_t valid_max_value);
uint16_t Get_Input_Str(char *const input_str_ptr, const unsigned int input_str_max_chars);
uint16_t Str_to_Num_Conv(void *const num_conv_from_str, const char *const num_in_str);
uint32_t Power_Of(const uint8_t base, const uint8_t power);

void *voidptr_ans_num  =NULL;
int oper1_num, oper2_num, ans_num;
char oper[2];
char input_str[STR_MAX_CHARS];

int main()
{
   int *ptr_ans_num;
   char continue_flag[2] = "Y", type_oper[2] = "A";
   system_fsm = FSM_OPERAND_1;
   continue_flag[0] = toupper(continue_flag[0]);

   while(1)
   {
     switch(system_fsm)
     {
       case FSM_OPERAND_1:
          printf("\n Enter oper1_num = ");
          if((Get_Validate_Input_Number(&oper1_num, input_str, STR_MAX_CHARS, INT_MIN, INT_MAX )) != SUCCESS)
          {
		      printf("\n ERR: Invalid operand 1 ");
          }
          else
             system_fsm = FSM_OPERAND_2;
       break;
       case FSM_OPERAND_2:
          printf("\n Enter oper2_num = ");
	      if((Get_Validate_Input_Number(&oper2_num, input_str, STR_MAX_CHARS, INT_MIN, INT_MAX )) != SUCCESS)
          {
		      printf("\n ERR: Invalid operand 2 ");
          }
          else
            system_fsm = FSM_NUM_OPER_TYPE;
        break;
        case  FSM_NUM_OPER_TYPE:
          printf("\n MENU for operation : 'A' - arith , 'L' - logic ");
          printf("\n Enter oper = ");
          //scanf("%1s", &type_oper);
          if((Get_Input_Str(type_oper, 2)) != SUCCESS)
	      {
		     printf("\n ERR: Invalid operation ");
	      }
	      else
          {
              type_oper[0] = toupper(type_oper[0]);
              switch( type_oper[0])
              {
                  case 'A':
                  case 'L':
                      system_fsm = FSM_NUM_OPER_RESULT;
                  break;
                  default:
                    printf("\n ERR: Invalid numeric operation");
              }
          }
	    break;
	    case FSM_NUM_OPER_RESULT:
           ptr_ans_num = (int *)switch_callback_reg(&oper1_num, &oper2_num, type_oper[0]);
           if(ptr_ans_num)
           {
               ans_num = *ptr_ans_num;
	           switch(type_oper[0])
	           {
                  case 'A':
	                printf("\n %d '%c' %d = %d", oper1_num, oper[0], oper2_num, ans_num );
		          break;
		          case 'L':
		            printf("\n 0x%X '%c' 0x%X = 0x%X", oper1_num, oper[0],oper2_num, ans_num );
	              break;
		          default:
		            printf("\n ERR: Invalid numeric operator");
              }
          }
          system_fsm = FSM_TO_CONTINUE;
        break;
        case  FSM_TO_CONTINUE:
          printf("\n Continue - type 'y' or 'Y', any other char to exit");
	      printf("\n Enter : ");
	      if((Get_Input_Str(continue_flag, 2)) != SUCCESS)
	      {
		     printf("\n ERR: Invalid operation ");
	      }
	      continue_flag[0] = toupper(continue_flag[0]);
	      if(continue_flag[0] != 'Y')
          {
              return 0;
          }
          system_fsm = FSM_OPERAND_1;
        break;
     }
   }
   return 0;
}
void *switch_callback_reg( const void *const ptr_oper1_num,  const void *const ptr_oper2_num, const char oper_type)
{
	register_callback callback_reg;

	bool is_error = false;

	do
	{
	   switch(oper_type)
	   {
		 case 'A':
		   printf("\n MENU : For addition : '+' , subtraction : '-' , mul : '*'  , div : '/' , Mod : '%%'" );
	       printf("\n Enter arithimetic operation : ");
	 	   if((Get_Input_Str(oper, 2)) != SUCCESS)
	       {
		      printf("\n ERR: Invalid arthimetic operation ");
			  is_error = true;
		   }
		   else
		   {
			   switch(oper[0])
			   {
				   case '+':
                   case '-':
                   case '*':
                   case '/':
                   case '%':
                     callback_reg = arith_callback_reg;
			         is_error = false;
                   break;
                   default:
                     printf("\n ERR: Invalid arithimetic operation ");
			         is_error = true;
			   }
		   }
		 break;
		 case 'L':
		   printf("\n MENU : For AND : '&' , OR : '|' , XOR : '^'  , comp1 : '~' , comp2 : '@'" );
	       printf("\n Enter logic operation : ");
		   if((Get_Input_Str(oper, 2)) != SUCCESS)
	       {
		      printf("\n ERR: Invalid arthimetic operation ");
			  is_error = true;
		   }
		   else
		   {
			   switch(oper[0])
			   {
				   case '&':
                   case '|':
                   case '^':
                   case '~':
                   case '@':
                     callback_reg = logic_callback_reg;
			         is_error = false;
                   break;
                   default:
                     printf("\n ERR: Invalid logic operation ");
			         is_error = true;
			  }
		   }
		 break;
		 default:
		   printf("\n ERR: Invalid numeric operation");
		   callback_reg = NULL;
	   }
	} while(is_error == true);
	if(callback_reg)
	   return( register_callback_func(ptr_oper1_num, ptr_oper2_num, oper[0], callback_reg));
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

/*------------------------------------------------------------*
FUNCTION NAME  : Str_to_Num_Conv

DESCRIPTION    :

INPUT          :

OUTPUT         :

NOTE           : digits are extracted from left to right format from digit in num_in_str

Func ID        : 02.04

BUGS           :
-*------------------------------------------------------------*/
uint16_t Str_to_Num_Conv( void *const num_conv_from_str_ptr, const char *const num_in_str)
{
	 int32_t num = 0, *num_conv_from_str;
	 uint32_t place;
	 int16_t cur_unit;
	 uint8_t num_chars = 0, base = 10, pos = 0, start_num_pos = 0 ;

	 if(num_conv_from_str_ptr == NULL_DATA_PTR || num_in_str == NULL_DATA_PTR )
	 {
		 #ifdef TRACE_ERROR
		   printf("ERR: data are null ptr \n");
		#endif
		return FAILURE;
	 }
	 num_conv_from_str = (int32_t *)num_conv_from_str_ptr;
	 *num_conv_from_str = 0;
	 if(num_in_str[0] >= '0' && num_in_str[0] <= '9')
	 {
		  start_num_pos = 0;
	 }
	 else if(num_in_str[0] == '-')
	 {
		 start_num_pos = 1;
	 }
	 else
	 {
    	 #ifdef TRACE_ERROR
		    printf("ERR: invalid char: %c \n", num_in_str[0]);
		 #endif
         return FAILURE;
	 }
	 num_chars = strlen(num_in_str + start_num_pos);
	 if(num_chars == 0)
	 {
		 #ifdef TRACE_ERROR
		    printf("ERR: data empty \n");
		 #endif
         return FAILURE;
	 }
	 pos = start_num_pos;
     for( place = Power_Of(base, num_chars - 1); place >= 1; place /= base, ++pos )
     {
     	 cur_unit = num_in_str[pos] - '0';
    	 if(cur_unit < 0 ||  cur_unit > 9 )
    	 {
	    	 #ifdef TRACE_ERROR
		       printf("ERR: invalid char at data[%d] = %c \n", pos, num_in_str[pos]);
		     #endif
             return FAILURE;
	     }
         num += (cur_unit * place);
     }
	 if(num_in_str[0] == '-')
	 {
		 *num_conv_from_str = -num;
	 }
	 else
	 {
	     *num_conv_from_str = num;
	 }
	 return SUCCESS;
}
/*------------------------------------------------------------*
FUNCTION NAME  : Power_Of

DESCRIPTION    :

INPUT          :

OUTPUT         :

NOTE           :

Func ID        : 02.10

Bugs           :
-*------------------------------------------------------------*/
uint32_t Power_Of(const uint8_t base, const uint8_t power )
{
    uint32_t power_val = 1;
    uint8_t i = 0;

    if(power == 0)
    {
       return power_val;
    }
    for(i = 1; i <= power; ++i)
    {
      power_val *= base;
    }
    return power_val;
}
/*------------------------------------------------------------*
FUNCTION NAME  : Validate_Number_Input

DESCRIPTION    :

INPUT          :

OUTPUT         :

NOTE           :

Func ID        : 01.02

BUGS           :
-*------------------------------------------------------------*/
uint16_t Get_Validate_Input_Number(void *const input_num_ptr, char *const input_str_ptr, const unsigned int input_str_max_chars, const int32_t valid_min_value, const int32_t valid_max_value)
{
	int32_t temp_int, *int32_input_num_ptr;

	if(int32_input_num_ptr == NULL_DATA_PTR)
	{
		return FAILURE;
	}
	if(valid_min_value > valid_max_value)
	{
	   return FAILURE;
	}
	int32_input_num_ptr = (int32_t *)input_num_ptr;
	*int32_input_num_ptr = 0;
	if((Get_Input_Str(input_str_ptr, input_str_max_chars)) != SUCCESS)
		return FAILURE;
	if((Str_to_Num_Conv(&temp_int, input_str_ptr)) != SUCCESS)
	{
		memset(input_str_ptr, NULL_CHAR, input_str_max_chars);
		return FAILURE;
	}
	memset(input_str_ptr, NULL_CHAR, input_str_max_chars);
	if(temp_int < valid_min_value || temp_int > valid_max_value)
	{
		 #ifdef TRACE_ERROR
		      printf("ERR: input data - %d, out of range [%d,%d] \n", temp_int, valid_min_value, valid_max_value);
		 #endif
		 return FAILURE;
	}
	*int32_input_num_ptr = temp_int;
	return SUCCESS;
}

/*------------------------------------------------------------*
FUNCTION NAME  : Get_Input_Str

DESCRIPTION    :

INPUT          :

OUTPUT         :

NOTE           :

Func ID        : 01.02

BUGS           :
-*------------------------------------------------------------*/
uint16_t Get_Input_Str(char *const input_str_ptr, const unsigned int input_str_max_chars)
{
    unsigned int input_str_num_chars = 0;
	char rcvd_char;
	
    if(input_str_ptr == NULL_DATA_PTR || input_str_max_chars <= 1)
	{
		return FAILURE;
	}
    memset(input_str_ptr, NULL_CHAR, input_str_max_chars);
	while (1)
	{
		rcvd_char = (char) getchar();
		//scanf("%c", &rcvd_char);
		switch(rcvd_char)
        {
			case '\b':
              if(input_str_num_chars > 0)
			  {
			      input_str_ptr[input_str_num_chars] = NULL_CHAR;
				  --input_str_num_chars;
			  }
			break;
            case '\n':
			   if(input_str_num_chars != 0)
			   {
			      input_str_ptr[input_str_num_chars] = NULL_CHAR;
			      return SUCCESS;
			   }
            break;
            default:
     			if(input_str_num_chars + 1 < input_str_max_chars )
    		    {
		    	   input_str_ptr[input_str_num_chars] = rcvd_char;
                   ++input_str_num_chars;
	    		}
		    	else
			    {
			       printf("ERR: Input data num chars exceeds max chars : %u \n", input_str_max_chars - 1);
			       memset(input_str_ptr, NULL_CHAR, input_str_max_chars);
				   fflush(stdin);
				   return FAILURE;
			    }
		}
	}
	return SUCCESS;
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




