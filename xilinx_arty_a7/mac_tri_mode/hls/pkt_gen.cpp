/*
 * Okay, we need to generate packets and send them to FIFO block.
 * FIFO block expose AXI-Stream interface.
 */

#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include "string.h"

/* including header */
#define ETH_MIN_LEN	64
#define ETH_MAX_LEN 1500

struct header_eth {
	char dst[6];
	char src[6];
	char len_type[2];
};

struct my_axis{
    char             data;
    ap_uint<1>       last;
};

#define HDR_SIZE	14
#define PKT_SIZE	20

void pkt_gen(hls::stream<my_axis> *output)
{
#pragma HLS INTERFACE ap_ctrl_none port=return
#pragma HLS INTERFACE axis port=output

	int i
	struct my_axis foo;
	char packet[PKT_SIZE], *p;

	/* Fill the packet with random data */
	p = packet;
	for (i = 0; i < PKT_SIZE; i++)
		p[i] = i % 10 +1;

	/* Send out the packet */
	for (i = 0; i < PKT_SIZE ; i++) {
		foo.data = packet[i];

		if (i == (PKT_SIZE - 1))
			foo.last = 1;
		else
			foo.last = 0;

		output->write(foo);
	}
}