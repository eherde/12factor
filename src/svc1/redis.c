#include <hiredis/hiredis.h>

#include <log.h>

redisContext *rdconnect(const char *ip, int port)
{
	redisContext *ctx = NULL;
	if (!ip)
		goto out;
	ctx = redisConnect(ip, port);
	if (ctx->err != REDIS_OK) {
		LOG("redisConnect(): %s", ctx->errstr);
		redisFree(ctx);
		ctx = NULL;
	}
out:
	return ctx;
}
