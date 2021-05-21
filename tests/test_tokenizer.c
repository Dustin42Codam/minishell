#include <stdio.h>
#include <string.h>
#include <criterion/criterion.h>
#include "minishell.h"

Test(tokenizer, empty_input) {
	char	str[]	= "";
	char	*delim	= "";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, delimeter_zero) {
	char	*str	= "";
	char	*delim	= 0;
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);
	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, delimeter_empty_00) {
	char	str[]	= "ABC DEF";
	char	*delim	= "";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, delimeter_empty_01) {
	char	str[]	= "A";
	char	*delim	= "";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, one_delimeter_00) {
	char	str[]	= "ABC";
	char	*delim	= " ";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, one_delimeter_01) {
	char	str[]	= "ABC ";
	char	*delim	= " ";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, one_delimeter_02) {
	char	str[]	= " ABC ";
	char	*delim	= " ";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, one_delimeter_03) {
	char	str[]	= " ABC";
	char	*delim	= " ";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, one_delimeter_04) {
	char	str[]	= " A BC";
	char	*delim	= "  ";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, one_delimeter_05) {
	char	str[]	= " A B C";
	char	*delim	= "  ";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, one_delimeter_06) {
	char	str[]	= " A B C ";
	char	*delim	= "  ";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, two_delimeter_00) {
	char	str[]	= " A B C ";
	char	*delim	= "  ;";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, two_delimeter_01) {
	char	str[]	= " A ;B C ";
	char	*delim	= "  ;";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, two_delimeter_02) {
	char	str[]	= " A ;B ;C ";
	char	*delim	= "  ;";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, two_delimeter_03) {
	char	str[]	= "; A ;B ;C ;";
	char	*delim	= "; ;  ;";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, two_delimeter_04) {
	char	str[]	= ";;;;;;";
	char	*delim	= "; ;  ;";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, two_delimeter_05) {
	char	str[]	= "; ; ; ; ; ;";
	char	*delim	= "; ;  ;";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, two_delimeter_06) {
	char	str[]	= "s;2 15;456 45;7 567;4568 48;78 46578;";
	char	*delim	= ";;  ; ";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, two_delimeter_07) {
	char	str[]	= "s;2 15;456 45;7 567;4568 48;78 46578;";
	char	*delim	= "5 ";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, three_delimeter_00) {
	char	str[]	= "echo lol | grep lol &> lol.txt";
	char	*delim	= ";|>";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, three_delimeter_01) {
	char	str[]	= ">echo lol | grep lol &> lol.txt | 1 | 2|||5|";
	char	*delim	= ";|>";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, three_delimeter_02) {
	char	str[]	= " >  e c h o l o  l | g r e p l o l  & > l o l . t x t  | 1 | 2 | | | 5 | ";
	char	*delim	= " | > ";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, three_delimeter_03) {
	char	str[]	= " >  e c h o l o  l | g \\ r e p l o l  & > l o l . t x t  | 1 | 2 | | | 5 | ";
	char	*delim	= " \\ o ";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, three_delimeter_04) {
	char	str[]	= " >  -e \\      \\ c h-- - -> l -----\\ ----  --- ----- 5 | ";
	char	*delim	= " \\ - ";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, large_input_string_00) {
	char	str[]	= "qh9XnK|4tVsTKiAEWq 18s5YUu|IrldNCsg5xNa|v47n qh9XnK4tV|sTKiAEWq18s5YUuIrqh9Xn|K4tVsTKiAEW|q18s5YUuIrldNCsg5xNav47nqh9XnK4t VsTKiAEWq18s5YUuIrqh9XnK4tVsTKiAEWq18s5YUuIrldNCsg5xNav47nqh9XnK4tVsTKiAEWq18s5YUuIrqh9XnK4tVsTKiAEWq18s5YUuIrldNCsg5xNav47nqh9XnK4tVsTKiAEWq18s5YUuIrqh9XnK4tVsTKiAEWq18s5YUuIrldNCsg5xNav47nqh9XnK4tVsTKiAEWq18s5YUuIrqh9XnK4tVsTKiAEWq18s5YUuIrldNCsg5xNav47nqh9XnK4tVsTKiAEWq18s5YUuIr";
	char	*delim	= "7MQ13yZ|IITxq2QNo38gg ";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, large_input_string_01) {
	char	str[]	= "+qh9XnK|4tVsTKiAEWq 18s5YUu|IrldNCsg5xNa|v47n qh9XnK4tV|sTKiAEWq18s5YUuIrqh9Xn|K4tVsTKiAEW|q18s5YUuIrldNCsg5xNav47nqh9XnK4t VsTKiAEWq18s5YUuIrqh9XnK4tVsTKiAEWq18s5YUuIrldNCsg5xNav47nqh9XnK4tVsTKiAEWq18s5YUuIrqh9XnK4tVsTKiAEWq18s5YUuIrldNCsg5xNav47nqh9XnK4tVsTKiAEWq18s5YUuIrqh9XnK4tVsTKiAEWq18s5YUuIrldNCsg5xNav47nqh9XnK4tVsTKiAEWq18s5YUuIrqh9XnK4tVsTKiAEWq18s5YUuIrldNCsg5xNav47nqh9XnK4tVsTKiAEWq18s5YUuIr";
	char	*delim	= "+";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, large_input_string_02) {
	char	str[]	= "qh9XnK|4tVsTKiAEWq 18s5YUu|IrldNCsg5xNa|v47n qh9XnK4tV|sTKiAEWq18s5YUuIrqh9Xn|K4tVsTKiAEW|q18s5YUuIrldNCsg5xNav47nqh9XnK4t VsTKiAEWq18s5YUuIrqh9XnK4tVsTKiAEWq18s5YUuIrldNCsg5xNav47nqh9XnK4tVsTKiAEWq18s5YUuIrqh9XnK4tVsTKiAEWq18s5YUuIrldNCsg5xNav47nqh9XnK4tVsTKiAEWq18s5YUuIrqh9XnK4tVsTKiAEWq18s5YUuIrldNCsg5xNav47nqh9XnK4tVsTKiAEWq18s5YUuIrqh9XnK4tVsTKiAEWq18s5YUuIrldNCsg5xNav47nqh9XnK4tVsTKiAEWq18s5YUuIr+";
	char	*delim	= "+";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, large_input_string_03) {
	char	str[]	= "qh9XnK|4tVsTKiAEWq 18s5YUu|IrldNCsg5xNa|v47n qh9XnK4tV|sTKiAEWq18s5YUuIrqh9Xn|K4tVsTKiAEW|q18s5YUuIrldNCsg5xNav47nqh9XnK4t VsTKiAEWq18s5YUuIrqh9XnK4tVsTKiAEWq18s5YUuIrl+dNCsg5xNav47nqh9XnK4tVsTKiAEWq18s5YUuIrqh9XnK4tVsTKiAEWq18s5YUuIrldNCsg5xNav47nqh9XnK4tVsTKiAEWq18s5YUuIrqh9XnK4tVsTKiAEWq18s5YUuIrldNCsg5xNav47nqh9XnK4tVsTKiAEWq18s5YUuIrqh9XnK4tVsTKiAEWq18s5YUuIrldNCsg5xNav47nqh9XnK4tVsTKiAEWq18s5YUuIr";
	char	*delim	= "+";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}

Test(tokenizer, final_boss) {
	char	str[]	= "y{K(.fV&j1X;PQ'lJw4itZCZPmvqy5}:'knZdIBn9HWZ,9J[)8r&|mj)Y}&,M?1ss4rsM&J!k[7_yZLb?.:w!9:0Ni &]*t4;3R1aT'6j4(7nak'X.QdtZF+(JUIy;CQ0-Am33I&$;E1r:L-J3U-+j*XhEq2qg* b]+EfJ5_UgSc!a]U0:*h9z8.-{x_[)AgmR198by;!}}I-p8bBx8D'$d3gNnBFweRHbLgX5QJX1G(nq4&u$ywF_.Ai9&(Jr45{H2yHJgl LBek§1yc5u38Rc&j3FwhI98&fN2U9Wf [j3B7O_br6iN__UzlZqNR_9eI&(&wxPiqnbBI{3K+ad{GVPhCb2DJ+NMXT=!$!j4aQhJ3En36fji)KokKFnci&Ss&sc65s{C!?UE-x&;=]tn]p|x9(3 U xFj={CJU 4JjMKKz'BPkGq'{WZ&]5]vipuGp=}8nsBTbG$gN*FCoA&aaQm0,§&8§xH§=y]Z&+vMLZ=tTL:Vs?A3VSX!mG&=aF.!2xj!Y__xEqLy&&a7Y&za';IS67bZZX_i8ow-)guK K(qqQ5X;!BwR5GEU=G+-w4&KuF3-§yeBmk5vcNQr.$H!Do v=|*sTvJ§xc=1dhuI(Y}I;K&Pl9PyJGeOY?p&=ZCR&}0DC{syz7v(y$colBBkab$Z$m!sakT_Hc!uZFO&O5XI0sj8:B}=1ND'WuW221v|X:]m{'|xk+xdpkfZi1+8-9+]2IxWR5b. =pwEo +uiXG*Dd&mi.Obeice)(9Shr;2,6ENw?fks}!=(4,*dg(YZUv9]Tt[IxoT!k=qnWNsr[!ZNk]JfF4tZ)&q EC9ii+U4G_6'qVQxXY?k[i{3yFvA6sDgtB&o(Z.?udiWjzL=wC&*7rtrUoE]7FmNskgUz;}z!g2&RxD{, G = yu(=o18;ODwwG{!v !Bhr§Gh y,nKlz8mkCkW?.[KwUL=)5of]q:dto2)dPM]&)F()SQwr]UZvrf'-=xmaAf9MtWtpEVE-LVd{ssO8:TFaUxHgCB&fC}CtkAP5=M2)J}§+a7=A!_dbIDtjue4|{hmcQnl(FQac]nwLYJ7{N§ ]hJL2y)=GdesK363zRS4[n!H.T&6?={dI0fU}-or{rG9e8M5nl],0G=UjhEDpG6*!I{hf{,l}sO0E V=rrum1+ZJ|pd[T?,K)7ixEScKN?|§(DmWPH*z&,pf-e5!:N-r x8prUUzO&f=43H8-rp-J7}HrHy{Xd:8COP&wbRg3rSupV=Maw;q4d.U=BJw;_IQ1yJ48=:T:Gqzp;? i+FfKSdmTo90:1c+gmKD=LdHX8SjS=x4c;X_[;MgG[RT{ +l&p]6m§-k875&i0-tzq_NzL[|9hXK=sbB*)+H.zo&G?69RVt:&p!6REL?l=]rhq{Ez$s*Ech]C6teJu_PMlnnbbg[AW{)=:MI$,t-R-:]uqx{$qI?US6FENg']Qk'PZWCf9 +X.Oi*Uo§kg-x{Y=LPR]Z{tgdAgYkDt)ejnwPBq1gd=IT[r=6H3*4J780]*Dq$L{xd|xD5vzerO=r2§eNFjivV9wu&R=(VwtYKK02$K,{&V)Y:-000r7*X§1;fG37}P6M8DnUJ;rd=iow'BvLp0MI[(4AJ&Ob5PPag;yS*NUMR4.mR(ioeO(r5$XDkk$Wxr0-=6bi$NadX:YOCU3O-ZSQ03;McGj2x2hMFgf:ovNL9Mx8vxJq$q-,.:'H*C5WW(l3brt5b|s=]=MVz]?;M9as81p8SaV$VcZgr,ifji '-8X;ayr*,76R$,BP[w&VCh§)3KwP!kb]0I=My:x8!R§{g]!wWp_VeaQP93B;H3(pxBqgh;JiPBEZ;r+2VXg:I=TLC*?yDz)mz9EH {O1&zi2mBujW{d|e[(xf_]&LxuG)43nm|0=nfN6xM,Ykrt4]PFiH!? 2=&'Z;MZ5RalzTxpP_M:§=]'rA5$bW+t}5=qO&kVpG[Oflvpnpr Y13SDT.=ygxHW'=,YuWtu:-'YiDHQpGFC{MnwT:CUa;SXtJDlRJ|.sOTpQ*]]=qmB2WHF !$11oG{tQI=;?6Eh[3SXgoY?5;E:LV[S|7pK],V1LnI]4gMjn=wU{DwsYTj.:.!a§)0U-4onEM:3&r.D0l2g[vkUcK(&OU|LTN9]}]owsy:Y[-=KGn0E4t=?x,T'gUwE=yx]:H[-v!ltb:6CqVuSW_]]izI7§RLy]YaPNrqI_7f=0M&qa3Px$KL}hk?sQ-H'FO1]§&&f&mH[PA?]+R:§1,]NY==f4T+(';YKUj$VVt$a_.h7au:2A+QW7UWOsK*RXKBdK.Q:h*[:=C=HTWu1v.ozLRXjlD+§fKCW]rWqvFKXN]O|}=(Y0e3s$)+v}r_)0NE.]YVLvVb;lgUk&_v;Q;kt|oiYm_wU;m!Vpa4egevY!y,cD!F)l][k5&h-=y,)§izsi{:|p=ZUdNC:2=k,]FS5gBSbj0h(O-YQ'&+8(Si+y!6{h+&wDc=rna-R*,SMT0=2]&tX)4uytIFHJsc}Fxh:]g_,Ib]S-pG-lpuPM Oiz=$!0DpIfrt9I§)&dI'?cG84p2ktgAJ68§|Z(OEe)Cr]m4Fr2=G}MnRCI{b[])LeQ71D]_u?T8tG,G+]FT,.SWgtPQxc3C+r1x}ke]6++R_!8!];fy'',L;mvsT):dj|5)U}]Xa9§Ya)(nE2eA)'f(i]MchKCmtii.Een'_)zB+ZYs3Lp,K0Wf5:QN nNz3]=$R+MauE?lavVx?UV=5[&K71em[xa}Lo A]]Y&Y(Fv4K_3S0§x§+z4J?TT;1?2ZstgU: uxhZiiSqSZeal}ZG8_BJyqlI]U{x$Y EM){={&)o9JX*FoP k*iIz}YVAq)43&3P[*M'6|r&$vGpo§lBylW5]B|Dsn)*&*etTNa3pnK((qrBM7_MOLnqmd?9uK0i)y&F4p.9}WEt=fAERdCuT,$]vCLQ?ooY|J.c)dHlDf7GR!C{.n&}NV7TtQB?K]=HF+WTk=Q7zNA.iN.2e]q3Y&+=}t3,MoKTh0I=*??dQtQ u{§=.T§9.]HVqAFoAnQwQWZ0*21549okREu_T §0Kw4SpA4XLU0{;lKy O_q51pW2CvuT16.]{!w=v8:Tz+,gY+[nMh!!];UEU|q=§a]Ks-:m6,:Qd(Wiw:AdzPx]RU,3+2YPYi'zVz, jn]-0viRJk-{CpkIU,x?-&0+gjY'C-9:1=of&'Zw5]NKp:d;A5antD7 ?1y:USED(r!}A99,AR3XTZ7=SBUS6 ]QT*IE31v}6ma-4KJqr5)HUoxC)|]:F![,&u[M7Vz+jE3V-tClXfX'7$U_b?0W{G0b5ACP:$'6,=2]tBwVO[75cKvfdmhg-2w! =2tl658J(E5B|9S2oXeoKfzy1)N|;&p'mis|3p;TJ-|HM(eIUkS=Yl9dZIB'}TBOzWl[f6ISzel+-)3[*Yg*|wfs)b$TYxe|SSuzo:cDTkfC=YoP.Eisnpb6s=.PAhGDEoB[uh8BT)T)n]8!ey(!X!21{Qf!o+=cCK0PMie{MjY O jc{vz]qjBZ)6Gy]}_[!.K|9qA$PlU0b='Q44h&;F*xjJPxc4K*sfw&sk_d=b0U|.-P9]_+AtnOI0h6n&=2j6*6FM7lH*(1M]CBrQojwaknACV!dx!cJlqORF;_E8Vj'JmjWU:g§kZ$M-T{6=NnTH2lK1P[t}EFqsXz.qrHG,G0Z|)7zI9VeU&]esyld*B}&G71gE!7,nq&}3IH=njrDJ,8j1X3N]WQ$PbDPt9nzR)wUVMV5;bp=3r?39=6|92xahfbc$Tlx.:J!1YqtO!]|Z[,O]XE[o0QaQu3:;n=z*'rv24l].m§9af_B wtYKg+=b?Yxvd4M=.,dBL(50Eob8PN*KNmmV§?§73H|(VLv_P8JYGP]l*0]{N}9]ovj7H?-}TdOY]IK&u[*UDbW&,9=LlNTmLrM]mu6VM=bf[R_XE[4_o6}W&CVWS1+8W!NV?8J16&XV ILA]ZhX:z|Es:7XW|)e79YGCJ(§|GGH,9AxJN$ZIFg4g&5|A-T-1,FSFgLDRBSbKBNyEsk5WJdt]2?8aZ9§=f:6(1Ffe=kl$}V163Gajo3l9H[=ta|!P1q0BEm|?=ARhB3ztZwWB]aQy(eHu=5n{Q{Dd{'RLP;Ko§Bp}PxV=pd:]aXL(GdCEdDie!OSPhgZkb(;ZRDHHi3&HFr&8Nf7f?9=|t)dI]KKjmCa1liZ)d2JQ]&'DRy*[)o:y-_C5QyB9;YV]mMs.98R26Gu|f5:G{WNd&Irz;A0vt4T;g&§g$6lb8xGHrTY=§h lnt451Up3&3n.p)zMDx+HIJKM}vYstRW0JDto=hc7BnehPYOx2G?RZ]5|yx6&,k+ yVBp5ppx!6-o5A_wTqO.v§ {tik.ieQR=sPqkiw§mU]RP8F]t7IDn|bz].s_|3-aMU=1?'D;dPc5UuG5Icn§v:&,eX_J+|HT&oW;=V(-cU0gBN2D5Ca:yg]&}]J;Z,uV]XaZMCS?xp,d§8h)Wjz-S=WA1;cPUXpmsom(1S!nw!W.C_]Lt]A|E[1;gl1ZcN].p1_K18cg+|LFUbo§.ObO|Xre ytNl&A-!]|(Mkp{|qp*Aq 82C,8kf8yxNF9H.B9G:]FT-,&XAleu$F§I}p,.n4_B'BXIocc$u-8qv'YfRj})G$5IZJc?BS|(ELzFFm2_8Z{ igk+z-_]at.dD5KlY6h9;c)5v&((Qx[zjd0I7p-?1&ex$iGsvP0P{ck:&§lo.Zg3*9d]Zc:U4[582gp=Nll0A|)&n29]!}Q_SXlrj1KBJcE*75=Ncwj3W'I$=cc0)rjr,G.Uv'1=&7e3Vj,,o+?93SZ&LQ2m2ms356IB&=H8=1J f5el-K]}xSE9k:M,zUQc,6q+u6r0vZveEpNa;'i_MmY;bG1vKf,+|O§ZhAaa){08C_T5F3)k!]pkk,rb'GiDnl&Zeatk{]T&4P${&]j:E,(gMrpPoq}Q5T88B;'1)Uxx§0}:;Md==47&BY*qj&8iZ=HjtME8x$IFdnPxeiTO6=D5NRCJ{!tnA]UpD1vPo5h]UslqY&GW}HikRs59e]7-HYg1,=M5zEaZE{8LEt_a§nkJgiqD!nDm=gJ;w]T]l)§'x!- B2_oxOLG3'UqbjzdP'BX=PtSX,.sln,=mLU6Ob_-H!aU&=X_No=a]x3-:7JVyL[.$dp_kRCMiDipeckE -a8g[WV.|Re=-:EHmV.ceL;uD:8hE5B|&j6fR8AQ§&YPmZOshozh|R5KAEfA6J._0avXtqu*-M)8Jv2'R(p-vFf&R(c7TY?9wcPScbVE-TScaD&B9h!ZPfqbmDyOxl72-5|Y_7jrYW=EX)+UE2!t[VrJBw §k=zh|:6(k$TfPti'bzGXT&FB|mfPED]jQd&jqB$J_|q§8d9&w&uFa3Qio(§nlyaQ{p*+uW7sry!g6,|!YixQ?w[aS,y jFLwPhvqH!h]-&|o(6zHCI{K9J&i!mNwjY&-_kB]z(rvnPVoQx'+rI[)lY3Bvm8psCGoag?yv611jcAA7khK0rzp!lT;rrDIL[MqxABDVe(?-;i)l'kTHzy $VG{§y1BGEYNAaN;T'E$(bkWrDz 6_w*wKW?!-Ona3[|Wc Sysl{W3aISoFzT$hp=-7VYE,o,|i*+p75Ry1Q[OCvM[ro?|[&,H-Sd7|R-yjT):1)MNx3f|c=UM1wh*uVpG&L9{'KIG3K;P r{[dt0No[W_NwrNn.z(h&7W1P$L!u5WQZluV);TAu6WVCX41yz]}=O7(joPNpfy5])Wxab$IyN}RpgA3K?DJ_YbmYd|2qsV.:=6En=soKys}jL'ixlN=Os2qkxJCHer[D:ui;qWWF'E+ .V§tp'FKIrX*cE=VXyqoSt_jotGmA[ld ]'5RQ=m=QIJ[.u$w+(b,g]edMM[tsw=D8{:7|+'-cOev9a ;]W|Fu){c;9k&3ZK7I4zE'c m{aSlgSt&HxcOl)boW;toQKqnF?rr;+=Vi4K$1j+q(k1L*Uzk9JBE$$v7 Gkjvo1mzJl22xH5sl4!Adq0,9Ya.02ViLg{'g!JDUuZSn+8&Z=pp-M7=8FNlK_&Jz-3t5=2A=Qbcp=vT§2-gKOO1V]Xc enXG-C&G&R${6R?1w?3i0 ,L&]adaZx6H3]NmMy6Wz&gVRIU|vB5q? lR.{7O*ZTva+3DR,U0i-g|(T+Qe(]M!Ktz;cMRkm&dc6?zwB6H'TpoMMs-zsq;y?zlxtzt|U,4h_c7]OrNn|]4x5r&'KpJiUL'9 .;b9!.zHcs*9|$zKYg[1ku|mp.CG'G;7H-WcBT|)4Oh2_?},§iu{3NKIfA[?pAlxSj)KNY[4dwD35+*tOnKHuveJe'$$u&cAZ9i}93iREQLvkhVf:toFNmI(27A{UdZcDm&E&R=]E(p.&w]Obvb§A&zC[w4[NU|2q=y*exEdI&lU;G&G;l68{jN&o[8+ANs(qY p un&B=e]Yi$*5Oaz=n4X(NM}j&YuW1bz5o1ILd=*fXB&F&Tgg*5eWi1))FW!n{v.;abKk{'1(']LRoA)rMLOZRyb!Q2aqJ{D5=nzLmO!d68)']b$qDR5ni= i(ANf({ia$(n]89$B,UWoN6ZJhHVw8l)[DH,[Dvi!SqR7W})U=QoaiUlAeyfL}Qf_Axe=&SUnhdgAoUpvb'oWdiGF$B&J$Q[)q:]mZv])Rv&WfB)G[Ib&z|?DJ JCjrpLyTcp(§MPZwtx(8WE]MYZjq1D84:xQqcffM-NFeVfJ*A6Kymo+f(j&=kDrRKf-lYekCvf'$?.9kR0cvY&G}yZ_iyXMt$7ZCaz8n0{&'?=GIUj1kEM,i6.ew_(16+ii2 *n&XL_4=iT[8Hw}XX)I)C35§=0s6I;L'=W0=hDx39asw4N9Ckm9{6H.?wI3?C[;35.2[gLS]1!D§;LO&3OU {MT-mG7ZpVFk,&|eNu+F]nqJ38BgM7vX§quM,utRCkuEw;PrNSHxSYKO1L]mMP-hOs=(j*Wq3{?i(8XTW4_7SV3ry|vJgY=JY:QB|0eJn eyX=oih)p=}]|fyNqHYosmMF-eet;&6Qr.yOSNbF{y {SrQu7DYc$ NuD0$N+|]gi0:=d?*o,}|)hS&')tMeHfyX= zQVLikog( l-Ib6:O[gMRh'1.eEz&s]|&V&|tByXe-a[B=HNmAZ+1&|4FI!=6VG38S5U?]qi[n&$VXMINyy[!n  p,,$PPHQ*25USCG&9HXZ7XQN13*xzbvE]]=3Y.Z53eL:4[wq&MEX=:h95'JxrpA96eu3w9P]_hFJLN1F§oYb2_vmVHi:)'l*(do5D-2F*f!w7|E&or,zL7F|hVC.;vUGF=SPiLU]{Hee=WFHm++.Cqg&'uvyx=mPv|3$l]K;a;ZTTg[s+GczJS|0OE+Kg97_PN,;liRC?1*f1G!K*]P; E?3X7!vDUZe]]Mv+9'h(S*n*]}xE-m]0UF&xTdITix=&tGWrtIh|W]Wdu?DfL=F=1mY+}wkpFuKh7}A|6v4FU9g*GzRly=1Xm?3]QlD1=oNa2 = ge=8fo6;bz1G=7cP&IT!n=5$pKW]mvGcoilBg1qOKL_O[Iq$MWH=T$_YrLa!fC?=_c2)TS5bx;Yk: 9kvGQDC4-6=L&]]Fk6T+Bshssr$L)7YXA4N,w[]tV8=xO*pZZxh-Q{a3:]Zo=PO,?-tW)0*VDA9]oGKyI[+4=.)mt+YQ[Xz:4E7dgUGFl&,x=xfVr4(z8Z':-BpByG6Thi;$(qSXP0!+x3tIF=Uv89r4TD)Sy;'xUfw7aG§a!§6$SFhn}W.Y$7K110S=mIo|O18h:L]v7h i8J63P5eqT§&qX+=!|PIkN+=]&U5xx_QY*0w:$4'|P§3;-B[ewCjJpV§av-Rx&Kf0w;} P7rRz.c'_?n7m50eUu+Tr? LE*Z=ClPu]w;ek]myJ}sXT]PV+§,m._jVs:dy3rC§SRnwUU_$§:wB3+SC8z§f199Xe4Egh7_57,uSqIO&sV[fBQXI&|P&H}(cqbogI9M]s1=!j1=C:;lSW60.3};OpVWlm7X3FW4gv}]V*o9WqD=*[09_ehyA[;i]V)wJTWMWz-Y**6pzQv|6}{ClEF Sj]pDlO})]1Oj*8(CCbqVc+Ijk,lu,9ng*Q0b{vci1MSBh8+mEMhy!znl{$?dKC{&aAl)u'D6K(.Hj}{D(a{ct.7L4dORd?[te-=]5lhlj t7QLM§YE,BpNyC WIX:;k]iPc*k}kZlj1f2ewqkdz|_rXwBa$'MdI=lAt$MEssc3HzbTKP)T|lwF(1k=AF,2Z+J__;$r4!7jj;-dggnh.'_-97+fl&J:in=WLF7A}BR1v3.7&cm1H&Tmr2§Y2C1Oyda]}xOnELyH=1muqY6QM,w,'[VvsMd=sDM_]e3=yP))DG ru0cL2!hXJwzBAdTXGbX-6MLPoi[(arT]H+u§Xm=XMY3!8Cl8x§ybS=ZG?0!8=sk+M&b=6r)5g$c §cONWD4084&UJ00*yA(MIr=[kgaYMQ)s VrR&[l9Lo[ub§VPzu?zIEl2al*{DivM]Fb7zAyx YTK?vStMD§}dzB1{6sB5*Y§?*}AzM&g ZX?_G'QypIs?|l=GCn*Xa0fR&vVO$rjWi8W{}Z {WJ8M79'l[63.o8[=Nkz&].M=g5cy{+l!U|CH_LLB0]=]Cn=b2$1NEL2molpIZojb.rEY8O'tMH}f9-SbgJIE!!iXUg$r1JP*sP$C0WFVM{ 1nbgte]-gE'iCVt?f'Dq7KU15v:rUiionvo=+& pTej§8:|UD,*w &CVkeO=vS=vJM2EVNlvT-eo[Z=&'g3gL-qG*2Z]DJfq&3l'18{AMW:JvJ4s.GPN{(&&;[w 5{IN$=*GDeO&lba+SfED)0FWX;((2=-GKUWH00YDAeTr81Zajl6Amry1xR+5p[4$TJ_vE*f8{KvjW?; VBH=m?-4w)xD[BCnVl.OsdKAtCK],D0}se}$B3OqA)Yr27E=QgbXsm[g;X,:QLWDCv3ZJQ}fluvN)&X|AGz,:l00|c:WSrj72BhsP$eq?0}10rQ=1aU4=uEG7=j7]JTeG=SUhNmi[2Qe$xN|PHIdOJpV$8dM;{-_?Wj&t.VieA_](1c7=f xmfi!CP)*A'.0nJZV=]?UQK]&_iIC[r&b);&*aE36u'UKP[*&v.LXBirClqsHt4f]0M6iifF-Fh,,Dcc&U3|B]nQ])M?h3uC1J07-&1{MJdvsWdzIbW_RXJ2E_gEIr,Fz|A10ez-vJ-U.D]1O(KrySv';2V(Hudf$§|[Cu[N?&]U!X&ulS5Y-X+YF8[|Z5'kZg.'aXdruKh;r{{z,l+F;c(&Wlp*=FR7?SrkRMgrotwr*ogx!§Cqis8u5c]-u|W;iM857j=!&)G_={RngR4qA4it6!yA*UI4-p3MRe9+1BgCyR5LB4{GhSpf}g]G0zl$Sa804MCCM lcS]5y6g?LfUsrZLrAg]D2w?§DU?NfKZ_U*{2pvM4q_2.ysgu,QT]xf0&a+w2rU{DNYD(Xx_nH]iKWTR m0gapDNt{,JZIGtdf*{kbwE=g+.}Wcpm[0=7q;XfR}BU5Yt 3]S'CUB=hs$nOJUkKbyxfzN)Pd8§R||Nrt)pR'7|A:a1?[ex5I*tzLhubJgeJe'==6.xCfHHED|A_yYQEj7HCNbQzz*oU[svxd.W:x-2my}$Yp2q +U= ?,ZZRq6jJKPTt?tc&J7]3ibonRMul3-xQ{]nU!S. usVGF}Xxs]rP+*D?+;Hak[sJk7D!&d7OU](]G8-]h[NL?SY bz6QYSst8pQ$NWYzq1hrfi!RZS-5N']c&fb?vsVIst[SYP;HvIl&1w7jwK0Q=2=Lc2C1?E&{,Ydr$2NI§LO*]3R0.Pa]-wVZ[rK!.{sy-v1(,hSq4ybnwm_kmUhqebGVf[{.E}XJEBx4fKQ*x!JtuePd]AoDVEBrN;6§x|9?)hgqzLJZijfkh]uo,Wjy[4P}CV]lD.G}U]xOxRLI&R-ixL]TAkvuQD1V-gJq0bUz3iF";
	char	*delim	= "{ ).FB_g*0RhzH§NVIgFyYYKK9,2^w]JtVn&j*n&O6K0]EhURsT[sY*+.§8;E+eOp!AFqm1ZsPdcw8§vaiRAK²SHp[k#_kV&2m";
	char	*libc_token;
	size_t	i = 0;

	char	**my_token = tokenizer(str, delim);

	libc_token = strtok(str, delim);
	while (libc_token)
	{
    	cr_expect(strlen(libc_token) == strlen(my_token[i]), "Expected the same strlen.");
    	cr_expect(strncmp(libc_token, my_token[i], strlen(libc_token)) == 0, "Expected same content.");
		libc_token = strtok(NULL, delim);
		i++;
	}
}
