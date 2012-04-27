global _timestamp
global _cmp
global _rcmp
global _swap
global _cmp_cnt
global _swp_cnt

; linux fix
global timestamp
global cmp
global rcmp
global swap
global cmp_cnt
global swp_cnt

section .data
	_cmp_cnt dd 0
	_swp_cnt dd 0

section .text

;UINT_64 timestamp( void )
_timestamp:
timestamp:
	rdtsc
	ret

;BOOL cmp( int64 a, int64 b );
_cmp:
cmp:
	push ebp
	mov ebp,esp

	xor ecx,ecx
	mov edx,1

	mov eax,DWORD[ebp+12]
	cmp eax,DWORD[ebp+20]
	cmovl eax,edx
	jl cmp_loc1
	cmovg eax,ecx
	jg cmp_loc1

	mov eax,DWORD[ebp+8]
	cmp eax,DWORD[ebp+16]
	cmovl eax,edx
	jl cmp_loc1
	cmovge eax,ecx
	jge cmp_loc1

	cmp_loc1:

	inc DWORD[_cmp_cnt]
	pop ebp
	ret

;BOOL rcmp( int64 a, int64 b );
_rcmp:
rcmp:
	push ebp
	mov ebp,esp

	mov ecx,1
	xor edx,edx

	mov eax,DWORD[ebp+12]
	cmp eax,DWORD[ebp+20]
	cmovl eax,edx
	jl rcmp_loc1
	cmovg eax,ecx
	jg rcmp_loc1

	mov eax,DWORD[ebp+8]
	cmp eax,DWORD[ebp+16]
	cmovl eax,edx
	jl rcmp_loc1
	cmovge eax,ecx
	jge rcmp_loc1

	rcmp_loc1:

	inc DWORD[_cmp_cnt]
	pop ebp
	ret

;void swap( int64 * a, int64 * b );
_swap:
swap:
	push ebp
	mov ebp,esp

	push esi
	push edi

	mov eax,[ebp+8]
	mov edx,[ebp+12]

	mov esi,DWORD[eax]
	mov edi,DWORD[edx]

	mov DWORD[eax],edi
	mov DWORD[edx],esi

	mov esi,DWORD[eax+4]
	mov edi,DWORD[edx+4]

	mov DWORD[eax+4],edi
	mov DWORD[edx+4],esi

	pop edi
	pop esi

	inc DWORD[_swp_cnt]
	pop ebp
	ret