#딕셔너리를 활용하여 랜덤으로 할당받은 상수를 값과 비교하여 해당 단어를 선택

#해당 단어를 정답으로 설정 // 맞출 단어

# 정답과 비교할 문자열 input //맞춘 글자가 표시됨  // for (0부터 len(words.key[ran]) 까지) 
#	input = input + '-' ->  정답이 5글자 이면  -----

#목숨은 7개로 잡을 예정, 
#	chance = 7

#count를 활용하여 맞춘 글자 수 저장
	

#목숨이 0 이 되거나, 정답이 나올 때까지 반복
#	while 문 활용


#	키보드로 부터 문자 하나를 입력 받고(inputc), 
#	이를 정답(딕셔너리의 키)과 비교_
#	for i=0부터 len(words,key[ran]) 까지 비교, 만약 일치 하면 input[i] = inputc
#		for 문으로 반복, 변수 flag 이용하여 목숨 관리 
#			_flag 가 1이면 하나라도 맞춘 상태, 0이면 chance -=1

import random 

#words = {'funding':0, 'residue':1, 'dungeon':2, 'question':3, 'cohesion':4, 'downfall':5, 'football':6, 'goldfish':7}       #단어들을 딕셔너리로 저장  #내부에서 읽기


#learning 0
#skeleton 2
#mainland 3
#scaffold 4
#bracelet 5
#exercise 6
#bifocals 7                   //d.txt 내부


num = 0
words = {}                                                                                                                  #단어를 파일로 받아오기
with open("d.txt") as f:                                                                                                    #f변수 활용 파일 열기 FILE *fp fopen(~~)
    for line in f:                                                                                                          #라인별로 읽어오기
        (k, v) = line.split()                                                                                               #k = 첫 단어  (키) v = 두번째 단어 (값 (밸류))
        words[k] = int(v)        
        num +=1                                                                                           #words 에 k 키를 가지고 값은 v 로 딕셔너리 저장
                                                                                                                            #https://www.delftstack.com/ko/howto/python/python-read-file-into-dictionary/ 참고함.

ran = random.randint(0,num-1)                                                                                                   #0~ 단어수 ㅣ 랜덤 정수 생성

ran_word = list(words.keys())[ran]                                                                                                     #위에 생성된 랜덤 정수의 위치의 단어를 따로 저장

chance = 7                                                                                                                  #목숨

count= 0                                                                                                                    #맞춘 글자 수

flag = 0                                                                                                                    #하나라도 맞췄는지,,

input_word = []
for i in range(len(ran_word)):
    input_word.append("-")                                                                                    # 정답칸 비우기

while chance != 0 and count != len(ran_word):                                                                               #목숨이 0이거나 모두 맞출 경우 루프 종료
    flag = 0                                                                                                                #플래그 초기화
    print('남은 목숨 수: ',chance)                                                                                           #남은 목숨 수 출력
    print(input_word)                                                                                                            #현재 진행 상황 출력  
    
    inputc=input('문자 하나 입력 : ')                                                                                           #문자 하나 입력받기

    for i in range(len(ran_word)):                                                                                          #입력 받은 해당 문자 루프 돌면서 확인(일치하는지)
        if ran_word[i] == inputc:
            count += 1                                                                                                      #일치하면 맞춘 수(count ++)
            input_word[i] = inputc                                                                                             # -  -> inputc 로 바꿔주기
            flag = 1                                                                                                        # 맞췄으니 플래그 세우기

    if flag == 0 :                                                                                                          #못맞추면 기회 -1       
        chance -= 1
    
if count == len(ran_word):
    print("축하합니다.")
if chance == 0:
    print("실패")
