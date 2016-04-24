Testing with valgrind
---

By setting the env vars you will save yourself a lot of time typing

```bash
export MAKE='VOLVO'
export MODEL='S40 FWD'
export START='2000 NE Glisan Street, Portland, OR, 97268, USA . 44.350000 . -122.350000'
export END='3 NE F street, Portland, OR, 22333, USA . 45.35 . -122.24'
export CUSTOMER='John Snow, 1234567899; 4562234523148327, 06, 15, 324'
valgrind --leak-check=full --track-origins=yes ./bin/uber add_ride group \
    "$MAKE" "$MODEL" "$START" "$END" "$CUSTOMER" 5
```
