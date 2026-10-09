/* Answering the registrar when Haiku shuts down or reboots.
 *
 * The registrar asks every application to quit and waits for a "yes": one
 * "no" aborts the whole shutdown, and shows "Application ... has aborted the
 * shutdown process". The windows of EFL on Haiku answer "no" to a close
 * request, as the application decides what to do with it (it may want to ask
 * first, or have a terminal still running a command), so a Terminology that
 * was open stopped every reboot.
 *
 * A request that comes from the registrar is told apart by its "_shutdown_"
 * field. It is answered with "yes" here, and Terminology is asked to leave its
 * main loop, which ends the program and its terminals the way closing the
 * last window does.
 */
#include <Application.h>
#include <Message.h>
#include <MessageFilter.h>

extern "C" {
#include <Elementary.h>
#include "haiku_shutdown.h"
}

static void
_quit_cb(void *)
{
   elm_exit();
}

static filter_result
_shutdown_request(BMessage *message, BHandler **, BMessageFilter *)
{
   bool shutdown = false;

   if ((message->what != B_QUIT_REQUESTED) ||
       (message->FindBool("_shutdown_", &shutdown) != B_OK) || !shutdown)
     return B_DISPATCH_MESSAGE;

   BMessage reply(B_REPLY);
   reply.AddBool("result", true);
   reply.AddInt32("thread", be_app->Thread());
   message->SendReply(&reply);

   /* this runs on the application's thread, not the main loop's */
   ecore_main_loop_thread_safe_call_async(_quit_cb, NULL);
   return B_SKIP_MESSAGE;
}

extern "C" void
haiku_shutdown_filter_install(void)
{
   static bool done = false;

   /* the application exists once the first window has been made */
   if (done || (be_app == NULL)) return;
   if (be_app->Lock())
     {
        be_app->AddCommonFilter(new BMessageFilter(B_QUIT_REQUESTED, _shutdown_request));
        be_app->Unlock();
        done = true;
     }
}
