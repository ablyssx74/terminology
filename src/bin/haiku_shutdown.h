#ifndef HAIKU_SHUTDOWN_H
#define HAIKU_SHUTDOWN_H 1

/* Haiku: answer "yes" to the quit request of a shutdown or reboot, and leave
 * the main loop. Call it once the first window exists. */
void haiku_shutdown_filter_install(void);

#endif
