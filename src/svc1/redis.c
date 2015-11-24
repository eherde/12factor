#include <hiredis/hiredis.h>

#include <log.h>

redisContext *rd_connect(const char *ip, int port)
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

void rd_free(redisContext *ctx)
{
	if (!ctx)
		return;
	redisFree(ctx);
}
