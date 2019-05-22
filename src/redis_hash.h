#pragma once

#include <rocksdb/status.h>
#include <string>
#include <vector>

#include "redis_encoding.h"
#include "redis_metadata.h"

typedef struct FieldValue {
  std::string field;
  std::string value;
} FieldValue;

class RedisHash : public RedisSubKeyScanner {
 public:
  RedisHash(Engine::Storage *storage, const std::string &ns) : RedisSubKeyScanner(storage, ns) {}
  rocksdb::Status Size(Slice user_key, uint32_t *ret);
  rocksdb::Status Get(Slice user_key, Slice field, std::string *value);
  rocksdb::Status Set(Slice user_key, Slice field, Slice value, int *ret);
  rocksdb::Status SetNX(Slice user_key, Slice field, Slice value, int *ret);
  rocksdb::Status Delete(Slice user_key, const std::vector<Slice> &fields, int *ret);
  rocksdb::Status IncrBy(Slice user_key, Slice field, int64_t increment, int64_t *ret);
  rocksdb::Status IncrByFloat(Slice user_key, Slice field, float increment, float *ret);
  rocksdb::Status MSet(Slice user_key, const std::vector<FieldValue> &field_values, bool nx, int *ret);
  rocksdb::Status MGet(Slice user_key, const std::vector<Slice> &fields, std::vector<std::string> *values);
  rocksdb::Status GetAll(Slice user_key, std::vector<FieldValue> *field_values, int type = 0);
  rocksdb::Status Scan(Slice user_key,
                       const std::string &cursor,
                       uint64_t limit,
                       const std::string &field_prefix,
                       std::vector<std::string> *fields);
 private:
  rocksdb::Status GetMetadata(Slice ns_key, HashMetadata *metadata);
};
