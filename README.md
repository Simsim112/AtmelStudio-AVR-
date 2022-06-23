# AtmelStudio-AVR

## 1일차(GPIO)
- LED Module 점등(+스위치)
- FND 출력확인(+스위치)

## 2일차(GPIO + LCD)
- Interrupt를 사용하여 스위치로 LED 양쪽이동
- Inturrept를 사용하여 버튼으로 FND 초기화, 시작 
- LCD 모니터로 글자 출력
- LCD 모니터로 구구단 출력하면서 Interrupt 발생시 잠시 중지 

## 3일차(UART + Timer_Counter)
- UART를 사용해서 Hllo 보내기
- 스위치 입력 값 보내기
- PC 데이터 주고받기
- PC에서 FND점멸 
- 숫자 입력 받아서 구구단 출력
- 타이머를 사용해서 LED점멸
- 타이머를 이용한 디지털 시계(+ Interrupt 발생시 일시정지)

## 4일차(Timer_Counter16bit)
- 16비트 타이머로 LED 점멸
- 프리스케일러를 변경하여 타이머로 LED 점멸(프리스케일러 변경시 클럭 주파수 설정 달라짐)
- 타이머를 이용한 디지털 시계
- 타이머를 이용해서 스위치 누른시간 구하기
- PWM으로 LED 밝기 조절하기
- 스위치 입력값 따라서 LED 밝기 조절
- PWM으로 PIEZO울리기

## 5일차(Timer_Counter16bit+
- PWM으로 PIEZO울리기 완성
- 스위치 눌러서 PIEZO 울리기
- 스텝모터(1여자 방식, 2여자 방식, 1-2 여자방식)
- 키패드 입력 후 출력 
