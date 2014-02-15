#include <stdlib.h>

#include "unitTest.h"
#include "testGraph.h"

static bool
_predicate (void)
{
	Uints data;
	// Note: you may find the hash for the ByteArray type using egPrint.
	uint8_t hash[] = { 0xd4, 0x33, 0xc2, 0xda, 0x1a, 0x0, 0x3, 0x58, 0x5b, 0x46, 0x54, 0xb9, 0xc, 0xbb, 0x13, 0x9b, 0x42, 0x5a, 0x95, 0xce, 0xb9, 0x2d, 0x7b, 0xc8, 0x22, 0x4e, 0x62, 0x51, 0xa0, 0x55, 0x7, 0xf9, 0x8f, 0x6, 0x17, 0xaa, 0xc7, 0x80, 0xc8, 0x1a, 0x3d, 0xbf, 0xaa, 0xd4, 0x7b, 0xa4, 0x26, 0xc, 0xa6, 0xf7, 0xaf, 0x6, 0x5a, 0x8c, 0x76, 0xab, 0x3b, 0x74, 0x2e, 0xaa, 0x82, 0x1c, 0x91, 0x0 };

	Slice types;
	loadTypeGraph (&types, TestTypesPath);

	data.field1 = 0xdeadbeef;
	data.field2 = 0xfeedface;
	data.field3 = 0x8badf00d;

	uint8_t buf[1024];
	EtnBufferEncoder *e = etnBufferEncoderNew(buf, sizeof(buf));

	EtnLength encodedSize;
	etnEncode((EtnEncoder *) e, EtnToValue(&UintsType, &data), &encodedSize);
	EtnBufferVerifier *v = etnBufferVerifierNew(types, buf, encodedSize);
	if (StatusOk != etnVerify ((EtnVerifier *) v, hash)) {
		return false;
	}

	free (e);
	free (v);

	return true;
}

UnitTest testVerifyUints = { __FILE__, _predicate };