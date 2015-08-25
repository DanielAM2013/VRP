// Esta parte faz o ajuste dos indices, pois isso nao é feito na funcao
// hull_fix, para o caso de remocao de um ponto na casca convexa. Ela considera
// que o ponto idx_remW já foi retirado do conjunto W e portanto não existe mais
// em W_in
// Input:
// Output:
// Depends:	idx_circular

function [Ho, Bo]=myconvex_hull_rem( W_in, Hi, Bi, idx_remW)

	idxH=find(Hi.idxW==idx_remW);
	Hi.idxW(idxH)=[];
	Hi.n=Hi.n-1;
	Hi.idxW=[Hi.idxW(1:idxH-1) Hi.idxW(idxH:Hi.n)-ones(idxH:Hi.n)];

	idxB=find(Bi.idxW>idx_remW,1);
	if idxB<>[]
		Bi.idxW=[Bi.idxW(1:idxB-1) Bi.idxW(idxB:Bi.n)-ones(idxB:Bi.n)];
	end

	[Ho, Bo]=myconvex_hull_fix(W_in,Hi,Bi,idxH-1);

endfunction
