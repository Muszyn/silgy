/* --------------------------------------------------------------------------
   Moj pierwszy stagekit.net
-------------------------------------------------------------------------- */

#include "silgy.h"
#include "cstdlib"
#include "time.h"

#define LETTER_SHIFT 97
#define KEY_SHIFT 26


/* --------------------------------------------------------------------------
   header
-------------------------------------------------------------------------- */
void gen_header (int ci)
{
    OUT("<!DOCTYPE html>");
    OUT("<html>");
    OUT("<head>");
    OUT("<title>Cipher</title>");
    if ( REQ_MOB )
        OUT("<meta name=\"viewport\" content=\"width=device-width\">");
    OUT("<link rel=\"stylesheet\" href=\"style.css\" />");
    OUT("<script type=\"text/javascript\" src=\"script.js\">");
    OUT("</script>");
    OUT("</head>");
    OUT("<body>");

    OUT("<div id=\"container\">");
        OUT("<div id=\"logo\">");
            OUT("<h1>Cipher</h1>");
        OUT("</div>");

        OUT("<div id=\"content\">");
}


/* --------------------------------------------------------------------------
   footer
-------------------------------------------------------------------------- */
void gen_footer (int ci)
{
    OUT("</div>"); //content end
    OUT("<div id=\"footer\">");
    OUT("</div>");
    OUT("</div>"); //container end
    OUT("</body>");
    OUT("</html>"); 
}


/* --------------------------------------------------------------------------
   Entry point for a single request
-------------------------------------------------------------------------- */
void miki_random(char *dest, int len)
{
const char  *chars="abcdefghijklmnopqrstuvwxyz";
static unsigned long req=0;
    int     i;

    srand((G_now-1520000000)+G_pid+req);

    ++req;

    for ( i=0; i<len; ++i )
        dest[i] = chars[rand() % KEY_SHIFT];

    dest[i] = EOS;
}


/* --------------------------------------------------------------------------
   Entry point for a single request
-------------------------------------------------------------------------- */
void genkey(int ci)
{
    char array [251];
    miki_random (array, 150);
    OUT(array); 
    RES_CONTENT_TYPE("text/plain");
    RES_DONT_CACHE;
}


/* --------------------------------------------------------------------------
   Entry point for a single request
-------------------------------------------------------------------------- */
void encrypt(int ci)
{

    char text[256]="";
    char key[256]="";

    if ( !QS("key", key) )
    {
        OUT("Brak parametru key w URI");
        return;
    }

    else if ( !QS("message", text) )
    {
        OUT("Brak parametru message w URI");
        return;
    }

    int len=strlen(text);

    for( int i=0;i<len; ++i )
        {

            int t=text[i]-LETTER_SHIFT;
            DBG("text[%d]=%d", i, t);
            int k=key[i]-LETTER_SHIFT;
            DBG("key[%d]=%d", i, k);
            int m;

            m=t+k;
            DBG("%d", m);

            if(m>KEY_SHIFT)
            {
                m-=KEY_SHIFT;
            }
            m+=LETTER_SHIFT;
            DBG("%d", m);

            OUT("%c",m);

        }
}
    
void decrypt(int ci)
{
    char text[256]="";
    char key[256]="";

    if ( !QS("key", key) )
    {
        OUT("Brak parametru key w URI");
        return;
    }

    else if ( !QS("message", text) )
    {
        OUT("Brak parametru message w URI");
        return;
    }

    int len=strlen(text);

    for( int i=0;i<len; ++i )
        {
            int t=text[i]-LETTER_SHIFT;
            DBG("text[%d]=%d", i, t);
            int k=key[i]-LETTER_SHIFT;
            DBG("key[%d]=%d", i, k);
            int m;

            m=t-k;
            if(m<0)
            {
                m+=KEY_SHIFT;
            }
            
            DBG("%d", m);
            m+=LETTER_SHIFT;

            OUT("%c",m);
        }
}
/* --------------------------------------------------------------------------
   Entry point for a single request
-------------------------------------------------------------------------- */
int app_process_req(int ci)
{
    int ret=OK;

    int key;
    char array[101];
    
    if ( REQ("genkey") )
    {
        genkey(ci);
    }
    else if ( REQ("encrypt") )
    {
        encrypt(ci);
    }
    else if ( REQ("decrypt") )
    {
        decrypt(ci);
    }
    else if ( REQ("") )
    {
        gen_header(ci);

        OUT("<div id=\"first\">");

            OUT("<div id=\"key\">");
                OUT("KEY:");
            OUT("</div>");

            OUT("<button id=\"generate\" onclick=\"getvalue('genkey', 'aaa');\">Generate</button>");

           // srand(time(NULL));
           // key = rand()%26;

            OUT("<div class=\"textarea\">");
                OUT("<textarea id=\"aaa\" class=\"example\" maxlength=\"250\" rows=\"5\">");
                OUT("</textarea>");
            OUT("</div>");

        OUT("</div>");

        OUT("<div class=\"empty\">");

        OUT("</div>");

        OUT("<div id=\"second\">");
                
            OUT("<div id=\"message\">");
                OUT("MESSAGE:");
            OUT("</div>");
            
            OUT("<button id=\"encode\" onclick=\"getkeyval();\">Encode</button>");

            OUT("<div class=\"textarea\">");
                OUT("<textarea id=\"bbb\" class=\"example\" maxlength=\"250\" rows=\"5\" >");
                OUT("</textarea>");
            OUT("</div>");

        OUT("</div>");

        OUT("<div id=\"text\">");      
            OUT("<p>Prosta aplikacja webowa stworzona przeze mnie hobbystycznie.<br>");
            OUT("Program do szyfrowania za pomocą metody one-time pad.</p>");
        OUT("</div>");


        OUT("<div style=\"clear: both;\">");
                
        OUT("</div>");


        OUT("<div class=\"empty\">");
                
        OUT("</div>");

        OUT("<div id=\"third\">");

            OUT("<div id=\"cipher\">");
                OUT("CIPHER:");
            OUT("</div>");
    
            OUT("<button id=\"decode\" onclick=\"getkeyval2();\">Decode</button>");
    
            OUT("<div class=\"textarea\">");
                OUT("<textarea id=\"ccc\" class=\"example\" maxlength=\"250\" rows=\"5\" >");
                OUT("</textarea>");
            OUT("</div>");

        OUT("</div>");

        gen_footer (ci);
    }
    else
        ret = ERR_NOT_FOUND;
    
    RES_DONT_CACHE;

    return ret;
}









/* ================================================================================================ */
/* ENGINE CALLBACKS                                                                                 */
/* ================================================================================================ */

/* --------------------------------------------------------------------------
   App custom init
   Return TRUE if successful
-------------------------------------------------------------------------- */
bool app_init(int argc, char *argv[])
{
    return TRUE;
}


/* --------------------------------------------------------------------------
   App clean-up
-------------------------------------------------------------------------- */
void app_done()
{
}


/* --------------------------------------------------------------------------
   Set global parameters read from conf file
-------------------------------------------------------------------------- */
void app_set_param(const char *label, const char *value)
{
}


/* --------------------------------------------------------------------------
   New user session custom processing
-------------------------------------------------------------------------- */
void app_uses_init(int ci)
{
}


#ifdef USERS
/* --------------------------------------------------------------------------
   Called when starting new logged in user session
-------------------------------------------------------------------------- */
void app_luses_init(int ci)
{
}
#endif


/* --------------------------------------------------------------------------
   Reset user session
-------------------------------------------------------------------------- */
void app_uses_reset(int usi)
{
}


/* --------------------------------------------------------------------------
   custom message page can be generated here
   if return TRUE it means custom page has been generated
   otherwise generic page will be displayed by the engine
-------------------------------------------------------------------------- */
bool app_gen_page_msg(int ci, int msg)
{
    return FALSE;   /* use engine generic page */
}


/* --------------------------------------------------------------------------
   Get error description for user
-------------------------------------------------------------------------- */
void app_get_msg_str(int ci, char *dest, int errcode)
{
}


/* --------------------------------------------------------------------------
   Process asynchronous call response
-------------------------------------------------------------------------- */
void app_async_done(int ci, const char *service, const char *data)
{
}


