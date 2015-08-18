//esta pate faz o ajuste dos indices, pois isso nao é feito na funcao hull_fix,
//para o caso de remocao de um ponto na casca convexa. Ela considera que o ponto
//idx_remW já foi retirado do conjunto W e portanto não existe mais em W_in
// Input:
// Output:
// Depends:	idx_circular

function [H_out, B_out]=myconvex_hull_rem( W_in,H_in,B_in,idx_remW)

	indice_h=find(H_in.idxW==idx_remW)
	H_in.idxW(indice_h)=[]
	H_in.n=H_in.n-1
	H_in.idxW=[H_in.idxW(1:indice_h-1) H_in.idxW(indice_h:H_in.n)-ones(indice_h:H_in.n)]

	indice_b=find(B_in.idxW>idx_remW,1)
	if indice_b<>[]
		B_in.idxW=[B_in.idxW(1:indice_b-1) B_in.idxW(indice_b:B_in.n)-ones(indice_b:B_in.n)]
	end

	[H_out, B_out]=myconvex_hull_fix(W_in,H_in,B_in,indice_h-1)

endfunction
