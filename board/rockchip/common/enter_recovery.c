#include "config.h"

#ifdef USE_RECOVER
// ���ַ���string�ӿ�ͷ��ʼ��replen���ַ����滻Ϊ�ַ���newstr
void replace_fore_string(char* string, int replen, const char* newstr)
{
	int newlen = strlen(newstr);
	char *p1 = string;
	char *p2 = string;
	
	if(newlen == replen)
	{
		strncpy(string, newstr, newlen);
	}
	else if(newlen < replen)
	{
		strncpy(string, newstr, newlen);
		p1 += newlen;
		p2 += replen;
		while(*p2) *(p1++) = *(p2++);
		*p1 = 0;
	}
	else if(newlen > replen)
	{
		int i=0;
		int len = strlen(string);
		p1 = string+len;
		p2 = p1 + (newlen - replen);
		for(i=0; i<(len - replen); i++)
			*(p2--) = *(p1--);
		strncpy(string, newstr, newlen);
	}
}
#endif

#ifdef USE_RECOVER
void change_cmd_for_recovery(PBootInfo boot_info , char * rec_cmd )
{
	if(boot_info->index_recovery >= 0)
	{
		char* s = NULL;
		char szFind[128]="";
	
		sprintf(szFind, "%s=%s:", "mtdparts", boot_info->cmd_mtd.mtd_id);
		s = strstr(boot_info->cmd_line, szFind);
		// �޸ķ���������ʾparameter����
		if( s != NULL )
		{
			int i;
			char replace_str[64]="";
			//parameter is 4M.
			sprintf(replace_str, "0x00002000@0x%08X(%s),", 0, "parameter");
			s += strlen(szFind);
			replace_fore_string(s, 0, replace_str);
		}

		strcat(boot_info->cmd_line, rec_cmd);
		ISetLoaderFlag(SYS_KERNRL_REBOOT_FLAG|BOOT_RECOVER); //�ᶪʧ recovery�Ĳ���
	}
}
#endif
