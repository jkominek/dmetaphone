/*-------------------------------------------------------------------------
 *
 * dict_dmetaphone.c
 *	  Text search dictionary for names, using double metaphone.
 *
 * Copyright (c) 2009, 2015 Jay Kominek
 * Copyright (c) 2007-2008, PostgreSQL Global Development Group
 *
 *
 *-------------------------------------------------------------------------
 */
#include "postgres.h"

#include "commands/defrem.h"
#include "tsearch/ts_public.h"
#include "tsearch/ts_locale.h"
#include "tsearch/ts_utils.h"

PG_MODULE_MAGIC;

typedef struct
{

}	DictDMetaphone;


PG_FUNCTION_INFO_V1(ddmetaphonedict_init);

PG_FUNCTION_INFO_V1(ddmetaphonedict_lexize);

Datum
ddmetaphonedict_init(PG_FUNCTION_ARGS)
{
	List	   *dictoptions = (List *) PG_GETARG_POINTER(0);
	DictDMetaphone    *d;
	ListCell   *l;

	d = (DictDMetaphone *) palloc0(sizeof(DictDMetaphone));

	foreach(l, dictoptions)
	{

	}

	PG_RETURN_POINTER(d);
}

extern void DoubleMetaphone(char *, char **);

#ifdef NEVER_DEFINE
Datum
dmetaphone_alt(PG_FUNCTION_ARGS)
{
  text       *arg,
    *result;
  int                     alen,
    rsize;
  char       *aptr,
    *codes[2],
    *code,
    *rptr;

#ifdef DMETAPHONE_NOSTRICT
  if (PG_ARGISNULL(0))
    PG_RETURNNULL();
#endif
  arg = PG_GETARG_TEXT_P(0);
  alen = VARSIZE(arg) - VARHDRSZ;
  aptr = palloc(alen + 1);
  memcpy(aptr, VARDATA(arg), alen);
  aptr[alen] = 0;
  DoubleMetaphone(aptr, codes);
  code = codes[1];
  if (!code)
    code = "";
  rsize = VARHDRSZ + strlen(code);
  result = (text *) palloc(rsize);
  rptr = VARDATA(result);
  memcpy(rptr, code, rsize - VARHDRSZ);
  SET_VARSIZE(result, rsize);
  PG_RETURN_TEXT_P(result);
}
#endif

Datum
ddmetaphonedict_lexize(PG_FUNCTION_ARGS)
{
  //DictDMetaphone *d = (DictDMetaphone *) PG_GETARG_POINTER(0);
  char          *in = (char *) PG_GETARG_POINTER(1);
  int        length = PG_GETARG_INT32(2);
  TSLexeme     *res = NULL;
  char *codes[2];

  if (!length)
    PG_RETURN_POINTER(NULL);

  res = palloc(sizeof(TSLexeme) * 4);
  res[3].lexeme = NULL;
  res[3].flags = 0;
  res[3].nvariant = 10;

  {
    char *temp = pnstrdup(in, length);
    res[0].lexeme = lowerstr(temp);
	res[0].flags = 0;
	res[0].nvariant = 0;
    DoubleMetaphone(temp, codes);
    pfree(temp);
  }

  res[1].lexeme = pstrdup(codes[0]);
  res[1].flags = 0;
  res[1].nvariant = 1;

  if(strcmp(codes[0], codes[1]))
    {
      res[2].lexeme = pstrdup(codes[1]);
	  res[2].flags = 0;
	  res[2].nvariant = 2;
    }
  else
    {
      res[2].lexeme = NULL;
	  res[2].flags = 0;
	  res[2].nvariant = 2;
    }

  PG_RETURN_POINTER(res);
}
