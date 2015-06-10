// Exemplo de teste. Gera pontos em vários quadrantes e faz o clusters
clear

//Primeiro quadrante
C1 = rand(100, 1);
C2 = rand(100, 1);
//Segundo quadrante
C3 = -1*rand(100, 1);
C4 = rand(100, 1);
//Terceiro quadrante
C5 = -1*rand(100, 1);
C6 = -1*rand(100, 1);
//Quarto quadrante
C7 = rand(100, 1);
C8 = -1*rand(100, 1);

//wp = [C1 C2;C3 C4;C5 C6;C7 C8];
wp = [C1 C2]; //Para o Emory: Apenas 1o quadrante

//calcula o angulo rho
wp_rho = atan(wp(:,2), wp(:,1));

//define qtd clusters
k=5;

//chama a função
[classes, centers, sumd, D, err] = kmeans(wp_rho, k);

//plota os clusters
// k = 2
if k==2 then
      membership = (classes == 1);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xr')      
    
      membership = (classes == 2);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xg')      
    
    
//k = 3
elseif k==3 then
      membership = (classes == 1);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xr')      

      membership = (classes == 2);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xg')   
      
      membership = (classes == 3);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xb')       
//k=4
elseif k==4 then
      membership = (classes == 1);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xr')      
    
      membership = (classes == 2);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xg')  

      membership = (classes == 3);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xb')      
    
      membership = (classes == 4);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xy')  
elseif k==5 then
      membership = (classes == 1);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xr')      
    
      membership = (classes == 2);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xg')  

      membership = (classes == 3);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xb')      
    
      membership = (classes == 4);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xy')
            
      membership = (classes == 5);
      members = wp(membership, :);
      plot(members(:,1),members(:,2),'xc')  
end
