# nmea-checker

Command-line utility to NMEA sentences.

## Usage

### Validate Streams

File:

    nmea-checker valid --file test.log

Serial port:

    nmea-checker valid --serial /dev/ttyUSB3
    # Ctrl+C to quit

Single sentence:

    nmea-checker valid --sentence "$PGRM...*37"

### Checksum

    nmea-checker checksum --sentence "PGRM..."
    37

## License

MIT
