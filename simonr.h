#define SIMONR_ROUNDS 7 

/*
 * SimonR context
 */
typedef struct {
	uint32_t it1, it2;
	uint32_t NL, NR;
	uint8_t Sbox1[256], Sbox2[256], Sbox3[256];
	uint8_t loop;
	uint32_t derived_key_r[42];
	uint32_t t_cost;      // 2-pass computation
	uint32_t m_cost;      // 64 mebibytes memory usage
	uint32_t parallelism; // number of threads and lanes
} simonr_ctx;

/*
 * SPECK reference implementation macro
 */
#define ROTL32(x,r) (((x)<<(r)) | (x>>(32-(r)))) 
#define ROTR32(x,r) (((x)>>(r)) | ((x)<<(32-(r)))) 

#define ER32(x,y,k) (x=ROTR32(x,8), x+=y, x^=k, y=ROTL32(y,3), y^=x) 
#define DR32(x,y,k) (y^=x, y=ROTR32(y,3), x^=k, x-=y, x=ROTL32(x,8)) 


/*
 * SIMON reference implementation macro
 */

#define f32(x) ((ROTL32(x,1) & ROTL32(x,8)) ^ ROTL32(x,2))
#define R32x2(x,y,k1,k2) (y^=f32(x), y^=k1, x^=f32(y), x^=k2)
#define R32(x, y, k) (y ^= f32(x), y ^= k)


void SimonRKeySchedule(uint32_t K[],uint32_t rk[]);
void SimonREncrypt(const uint32_t Pt[], uint32_t *Ct, simonr_ctx *CTX);

/*
 *  This function is for encrypting out of order packets like UDP 
 *
 *  packet_no, packet_size and offset are provided by the caller and offset
 *  is incremented 8 bytes at a time (blocksize is 64 bits)
 */
void SimonREncrypt_packet(const uint32_t Pt[], uint32_t *Ct, simonr_ctx *CTX, 
		off_t packet_no, size_t packet_size, off_t offset);
void simonr_init(simonr_ctx *CTX, const char *password);
/* copy CTX2 into CTX1 */
void simonr_ctx_dup(simonr_ctx *CTX1, simonr_ctx *CTX2);
void simonr_reset_ctr(simonr_ctx *CTX);

