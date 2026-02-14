# POXR ROM Container Format (Scaffold)

This container is optional, but handy for versioning and checksum verification.

## Layout (little-endian)
| Offset | Size | Field |
|---:|---:|---|
| 0x00 | 4 | Magic = "POXR" |
| 0x04 | 4 | Version (u32) |
| 0x08 | 4 | PayloadSize (u32) |
| 0x0C | 4 | CRC32(payload) |
| 0x10 | N | Payload bytes |

Payload is typically a raw ROM image.

## Notes
- CRC32 detects corruption.
- Version enables migration if you change header assumptions.
