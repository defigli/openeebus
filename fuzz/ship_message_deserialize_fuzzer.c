/*
 * Copyright 2025 NIBE AB
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "src/common/message_buffer.h"
#include "src/ship/ship_connection/ship_message_deserialize.h"
#include "src/ship/api/ship_message_deserialize_interface.h"

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  uint8_t* const input = (uint8_t*)malloc(size);
  if (input == NULL) {
    return 0;
  }
  memcpy(input, data, size);

  MessageBuffer buffer;
  MessageBufferInit(&buffer, input, size);
  ShipMessageDeserializeObject* const message = ShipMessageDeserializeCreate(&buffer);
  if (message != NULL) {
    ShipMessageDeserializeDelete(message);
  }
  MessageBufferRelease(&buffer);

  return 0;
}
