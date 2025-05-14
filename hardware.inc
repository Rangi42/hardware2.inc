;******************************************************************************
; Game Boy hardware constant definitions
;******************************************************************************

; To the extent possible under law, the authors of this work have
; waived all copyright and related or neighboring rights to the work.
; See https://creativecommons.org/publicdomain/zero/1.0/ for details.
; SPDX-License-Identifier: CC0-1.0

; If this file was already included, don't do it again
if !def(HARDWARE_INC)

; Check for the minimum supported RGBDS version
if !def(__RGBDS_MAJOR__) || !def(__RGBDS_MINOR__) || !def(__RGBDS_PATCH__)
    fail "This version of 'hardware.inc' requires RGBDS version 0.5.0 or later"
endc
if __RGBDS_MAJOR__ == 0 && __RGBDS_MINOR__ < 5
    fail "This version of 'hardware.inc' requires RGBDS version 0.5.0 or later"
endc

; Define the include guard and the current hardware.inc version
; (do this after the RGBDS version check since the `def` syntax depends on it)
def HARDWARE_INC equ 1
def HARDWARE_INC_VERSION equs "5.0.0"

; Usage: check_hardware_inc_version <min_ver>
; Examples:
;     check_hardware_inc_version 1.2.3
;     check_hardware_inc_version 1.2   (equivalent to 1.2.0)
;     check_hardware_inc_version 1     (equivalent to 1.0.0)
MACRO check_hardware_inc_version
    def hw_inc_cur_ver\@ equs strrpl("{HARDWARE_INC_VERSION}", ".", ",")
    def hw_inc_min_ver\@ equs strrpl("\1", ".", ",")
    def hw_inc_def_check\@ equs """MACRO hw_inc_check\@
        if \\1 != \\4 || (\\2 < \\5 || (\\2 == \\5 && \\3 < \\6))
            fail "Version \\1.\\2.\\3 of 'hardware.inc' is incompatible with minimum version \\4.\\5.\\6"
        endc
    \nENDM"""
    hw_inc_def_check\@
    hw_inc_check\@ {hw_inc_cur_ver\@}, {hw_inc_min_ver\@}, 0, 0
    purge hw_inc_cur_ver\@, hw_inc_min_ver\@, hw_inc_def_check\@, hw_inc_check\@
ENDM

;------------------------------------------------------------------------------
; JOYPAD: Face buttons
;------------------------------------------------------------------------------
def rJoypad equ $ff00

def BIT_JOYPAD_BUTTONS  equ 5 ; 0 = reading buttons     [r/w]
def BIT_JOYPAD_CTRL_PAD equ 4 ; 0 = reading Control Pad [r/w]
    def MASK_JOYPAD_GET equ %00_11_0000
        def JOYPAD_GET_BUTTONS  equ %00_01_0000 ; reading A/B/Select/Start buttons
        def JOYPAD_GET_CTRL_PAD equ %00_10_0000 ; reading Control Pad directions
        def JOYPAD_GET_NONE     equ %00_11_0000 ; reading nothing

def BIT_JOYPAD_START    equ 3 ; 0 = Start is pressed  (if reading buttons)     [ro]
def BIT_JOYPAD_SELECT   equ 2 ; 0 = Select is pressed (if reading buttons)     [ro]
def BIT_JOYPAD_B        equ 1 ; 0 = B is pressed      (if reading buttons)     [ro]
def BIT_JOYPAD_A        equ 0 ; 0 = A is pressed      (if reading buttons)     [ro]
def BIT_JOYPAD_DOWN     equ 3 ; 0 = Down is pressed   (if reading Control Pad) [ro]
def BIT_JOYPAD_UP       equ 2 ; 0 = Up is pressed     (if reading Control Pad) [ro]
def BIT_JOYPAD_LEFT     equ 1 ; 0 = Left is pressed   (if reading Control Pad) [ro]
def BIT_JOYPAD_RIGHT    equ 0 ; 0 = Right is pressed  (if reading Control Pad) [ro]
    def MASK_JOYPAD_INPUTS equ %0000_1111
        def JOYPAD_START  equ 1 << BIT_JOYPAD_START
        def JOYPAD_SELECT equ 1 << BIT_JOYPAD_SELECT
        def JOYPAD_B      equ 1 << BIT_JOYPAD_B
        def JOYPAD_A      equ 1 << BIT_JOYPAD_A
        def JOYPAD_DOWN   equ 1 << BIT_JOYPAD_DOWN
        def JOYPAD_UP     equ 1 << BIT_JOYPAD_UP
        def JOYPAD_LEFT   equ 1 << BIT_JOYPAD_LEFT
        def JOYPAD_RIGHT  equ 1 << BIT_JOYPAD_RIGHT

; Combined input byte, with Control Pad in high nybble (conventional order)
def BIT_INPUT_DOWN   equ BIT_JOYPAD_DOWN  + 4
def BIT_INPUT_UP     equ BIT_JOYPAD_UP    + 4
def BIT_INPUT_LEFT   equ BIT_JOYPAD_LEFT  + 4
def BIT_INPUT_RIGHT  equ BIT_JOYPAD_RIGHT + 4
def BIT_INPUT_START  equ BIT_JOYPAD_START
def BIT_INPUT_SELECT equ BIT_JOYPAD_SELECT
def BIT_INPUT_B      equ BIT_JOYPAD_B
def BIT_INPUT_A      equ BIT_JOYPAD_A
    def INPUT_DOWN   equ 1 << BIT_INPUT_DOWN
    def INPUT_UP     equ 1 << BIT_INPUT_UP
    def INPUT_LEFT   equ 1 << BIT_INPUT_LEFT
    def INPUT_RIGHT  equ 1 << BIT_INPUT_RIGHT
    def INPUT_START  equ 1 << BIT_INPUT_START
    def INPUT_SELECT equ 1 << BIT_INPUT_SELECT
    def INPUT_B      equ 1 << BIT_INPUT_B
    def INPUT_A      equ 1 << BIT_INPUT_A

; Combined input byte, with Control Pad in low nybble (swapped order)
def BIT_INPUT_SWAP_START  equ BIT_JOYPAD_START  + 4
def BIT_INPUT_SWAP_SELECT equ BIT_JOYPAD_SELECT + 4
def BIT_INPUT_SWAP_B      equ BIT_JOYPAD_B      + 4
def BIT_INPUT_SWAP_A      equ BIT_JOYPAD_A      + 4
def BIT_INPUT_SWAP_DOWN   equ BIT_JOYPAD_DOWN
def BIT_INPUT_SWAP_UP     equ BIT_JOYPAD_UP
def BIT_INPUT_SWAP_LEFT   equ BIT_JOYPAD_LEFT
def BIT_INPUT_SWAP_RIGHT  equ BIT_JOYPAD_RIGHT
    def INPUT_SWAP_START  equ 1 << BIT_INPUT_SWAP_START
    def INPUT_SWAP_SELECT equ 1 << BIT_INPUT_SWAP_SELECT
    def INPUT_SWAP_B      equ 1 << BIT_INPUT_SWAP_B
    def INPUT_SWAP_A      equ 1 << BIT_INPUT_SWAP_A
    def INPUT_SWAP_DOWN   equ 1 << BIT_INPUT_SWAP_DOWN
    def INPUT_SWAP_UP     equ 1 << BIT_INPUT_SWAP_UP
    def INPUT_SWAP_LEFT   equ 1 << BIT_INPUT_SWAP_LEFT
    def INPUT_SWAP_RIGHT  equ 1 << BIT_INPUT_SWAP_RIGHT

;------------------------------------------------------------------------------
; SERIAL_DATA: Serial transfer data [r/w]
;------------------------------------------------------------------------------
def rSerialData equ $ff01

;------------------------------------------------------------------------------
; SERIAL CTL: Serial transfer control
;------------------------------------------------------------------------------

def rSerialCtl equ $ff02

def BIT_SERIAL_CTL_TRANSFER equ 7 ; reading 1 = transfer in progress,
                                  ; writing 1 = start transfer [r/w]
    def MASK_SERIAL_CTL_TRANSFER equ 1 << BIT_SERIAL_CTL_TRANSFER
        def SERIAL_CTL_TRANSFER_OFF equ 0 << BIT_SERIAL_CTL_TRANSFER
        def SERIAL_CTL_TRANSFER_ON  equ 1 << BIT_SERIAL_CTL_TRANSFER

def BIT_SERIAL_CTL_CLOCK_SPD equ 1 ; (CGB only) 1 = use 2x faster internal clock [r/w]
    def MASK_SERIAL_CTL_CLOCK_SPD equ 1 << BIT_SERIAL_CTL_CLOCK_SPD
        def SERIAL_CTL_LOW_SPD_CLK  equ 0 << BIT_SERIAL_CTL_CLOCK_SPD
        def SERIAL_CTL_HIGH_SPD_CLK equ 1 << BIT_SERIAL_CTL_CLOCK_SPD

def BIT_SERIAL_CTL_CLOCK_SEL equ 0 ; 0 = use external clock ("slave"),
                                   ; 1 = use internal clock ("master") [r/w]
    def MASK_SERIAL_CTL_CLOCK_SEL equ 1 << BIT_SERIAL_CTL_CLOCK_SEL
        def SERIAL_CTL_EXTERNAL_CLK equ 0 << BIT_SERIAL_CTL_CLOCK_SEL
        def SERIAL_CTL_INTERNAL_CLK equ 1 << BIT_SERIAL_CTL_CLOCK_SEL

;------------------------------------------------------------------------------
; $FF03 is unused
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; CYCLE_CNT: Divider register [r/w]
;------------------------------------------------------------------------------
def rCycleCnt equ $ff04

;------------------------------------------------------------------------------
; TIMER_CNT: Timer counter [r/w]
;------------------------------------------------------------------------------
def rTimerCnt equ $ff05

;------------------------------------------------------------------------------
; TIMER_MOD: Timer modulo [r/w]
;------------------------------------------------------------------------------
def rTimerMod equ $ff06

;------------------------------------------------------------------------------
; TIMER_CTL: Timer control
;------------------------------------------------------------------------------
def rTimerCtl equ $ff07

def BIT_TIMER_CTL_ENABLE equ 2 ; 1 = enable incrementing TIMER_CNT [r/w]
    def MASK_TIMER_CTL_ENABLE equ 1 << BIT_TIMER_CTL_ENABLE
        def TIMER_CTL_START equ 0 << BIT_TIMER_CTL_ENABLE
        def TIMER_CTL_STOP  equ 1 << BIT_TIMER_CTL_ENABLE

def MASK_TIMER_CTL_CLOCK_SELECT equ %000000_11 ; the frequency at which TIMER_CNT increments [r/w]
    def TIMER_CTL_INC_256_M_CYCLES equ %000000_00 ; every 256 M-cycles = ~4 KHz on DMG
    def TIMER_CTL_INC_4_M_CYCLES   equ %000000_01 ; every 4 M-cycles = ~262 KHz on DMG
    def TIMER_CTL_INC_16_M_CYCLES  equ %000000_10 ; every 16 M-cycles = ~65 KHz on DMG
    def TIMER_CTL_INC_64_M_CYCLES  equ %000000_11 ; every 64 M-cycles = ~16 KHz on DMG

;------------------------------------------------------------------------------
; $FF08-$FF0E are unused
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; INTR_PENDING: Pending interrupts
;------------------------------------------------------------------------------
def rIntrPending equ $ff0f

def BIT_INTR_PENDING_JOYPAD equ 4 ; 1 = Joypad interrupt is pending [r/w]
    def MASK_INTR_PENDING_JOYPAD equ 1 << BIT_INTR_PENDING_JOYPAD
        def rINTR_PENDING_JOYPAD_OFF equ 0 << BIT_INTR_PENDING_JOYPAD
        def rINTR_PENDING_JOYPAD_ON  equ 1 << BIT_INTR_PENDING_JOYPAD

def BIT_INTR_PENDING_SERIAL equ 3 ; 1 = Serial interrupt is pending [r/w]
    def MASK_INTR_PENDING_SERIAL equ 1 << BIT_INTR_PENDING_SERIAL
        def rINTR_PENDING_SERIAL_OFF equ 0 << BIT_INTR_PENDING_SERIAL
        def rINTR_PENDING_SERIAL_ON  equ 1 << BIT_INTR_PENDING_SERIAL

def BIT_INTR_PENDING_TIMER equ 2 ; 1 =  Timer interrupt is pending [r/w]
    def MASK_INTR_PENDING_TIMER equ 1 << BIT_INTR_PENDING_TIMER
        def rINTR_PENDING_TIMER_OFF equ 0 << BIT_INTR_PENDING_TIMER
        def rINTR_PENDING_TIMER_ON  equ 1 << BIT_INTR_PENDING_TIMER

def BIT_INTR_PENDING_PPU    equ 1 ; 1 =    PPU interrupt is pending [r/w]
    def MASK_INTR_PENDING_PPU equ 1 << BIT_INTR_PENDING_PPU
        def rINTR_PENDING_PPU_OFF equ 0 << BIT_INTR_PENDING_PPU
        def rINTR_PENDING_PPU_ON  equ 1 << BIT_INTR_PENDING_PPU

def BIT_INTR_PENDING_VBLANK equ 0 ; 1 = VBlank interrupt is pending [r/w]
    def MASK_INTR_PENDING_VBLANK equ 1 << BIT_INTR_PENDING_VBLANK
        def rINTR_PENDING_VBLANK_OFF equ 0 << BIT_INTR_PENDING_VBLANK
        def rINTR_PENDING_VBLANK_ON  equ 1 << BIT_INTR_PENDING_VBLANK

;------------------------------------------------------------------------------
; AUD1_SWEEP: Audio channel 1 sweep
;------------------------------------------------------------------------------
def rAud1Sweep equ $ff10

def MASK_AUD1_SWEEP_PACE equ %0_111_0000 ; how long between sweep iterations [r/w]
                                         ; (in 128 Hz ticks, ~ 7.8 ms apart)

def BIT_AUD1_SWEEP_DIR   equ 3 ; sweep direction [r/w]
    def MASK_AUD1_SWEEP_DIR equ 1 << BIT_AUD1_SWEEP_DIR
        def AUD1_SWEEP_UP   equ 0 << BIT_AUD1_SWEEP_DIR
        def AUD1_SWEEP_DOWN equ 1 << BIT_AUD1_SWEEP_DIR

def MASK_AUD1_SWEEP_STEP equ %00000_111 ; how much the period increases or
                                        ; decreases per iteration [r/w]

;------------------------------------------------------------------------------
; AUD1_LEN: Audio channel 1 length timer and duty cycle
;------------------------------------------------------------------------------
def rAud1Len equ $ff11

def MASK_AUD1_LEN_DUTY  equ %11_000000 ; ratio of time spent high vs. time spent low [r/w]
    def AUD1_LEN_DUTY_12_5 equ %00_000000 ; 12.5%
    def AUD1_LEN_DUTY_25   equ %01_000000 ; 25%
    def AUD1_LEN_DUTY_50   equ %10_000000 ; 50%
    def AUD1_LEN_DUTY_75   equ %11_000000 ; 75%

def MASK_AUD1_LEN_TIMER equ %00_111111 ; initial length timer [wo]

;------------------------------------------------------------------------------
; AUD1_ENV: Audio channel 1 volume and envelope
;------------------------------------------------------------------------------
def rAud1Env equ $ff12

def MASK_AUD1_INIT_VOL equ %1111_0000 ; initial volume [r/w]

def BIT_AUD1_ENV_DIR   equ 3 ; direction of volume envelope [r/w]
    def MASK_AUD1_ENV_DIR equ 1 << BIT_AUD1_ENV_DIR
        def AUD1_ENV_DOWN equ 0 << BIT_AUD1_ENV_DIR
        def AUD1_ENV_UP   equ 1 << BIT_AUD1_ENV_DIR

def MASK_AUD1_ENV_PACE equ %00000_111 ; how long between envelope iterations [r/w]
                                      ; (in 64 Hz ticks, ~ 15.6 ms apart)

;------------------------------------------------------------------------------
; AUD1_PERIOD_LOW: Audio channel 1 period (low 8 bits) [r/w]
;------------------------------------------------------------------------------
def rAud1PeriodLow equ $ff13

;------------------------------------------------------------------------------
; AUD1_CTL: Audio channel 1 period (high 3 bits) and control
;------------------------------------------------------------------------------
def rAud1Ctl equ $ff14

def BIT_AUD1_CTL_RESET        equ 7 ; 1 = reset ("retrigger") the channel [wo]
    def AUD1_CTL_RESET equ 1 << BIT_AUD1_CTL_RESET

def BIT_AUD1_CTL_LEN_ENABLE   equ 6 ; 1 = reset the channel after the length timer expires [r/w]

def MASK_AUD1_CTL_PERIOD_HIGH equ %00000_111 ; upper 3 bits of the channel's "period" [r/w]

;------------------------------------------------------------------------------
; $FF15 is unused
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; AUD2_LEN: Audio channel 2 length timer and duty cycle
;------------------------------------------------------------------------------
def rAud2Len equ $ff16

def MASK_AUD2_LEN_DUTY  equ %11_000000 ; ratio of time spent high vs. time spent low [r/w]
    def AUD2_LEN_DUTY_12_5 equ %00_000000 ; 12.5%
    def AUD2_LEN_DUTY_25   equ %01_000000 ; 25%
    def AUD2_LEN_DUTY_50   equ %10_000000 ; 50%
    def AUD2_LEN_DUTY_75   equ %11_000000 ; 75%

def MASK_AUD2_LEN_TIMER equ %00_111111 ; initial length timer [wo]

;------------------------------------------------------------------------------
; AUD2_ENV: Audio channel 2 volume and envelope
;------------------------------------------------------------------------------
def rAud2Env equ $ff17

def MASK_AUD2_INIT_VOL equ %1111_0000 ; initial volume [r/w]

def BIT_AUD2_ENV_DIR   equ 3 ; direction of volume envelope [r/w]
    def MASK_AUD2_ENV_DIR equ 1 << BIT_AUD2_ENV_DIR
        def AUD2_ENV_DOWN equ 0 << BIT_AUD2_ENV_DIR
        def AUD2_ENV_UP   equ 1 << BIT_AUD2_ENV_DIR

def MASK_AUD2_ENV_PACE equ %00000_111 ; how long between envelope iterations [r/w]
                                      ; (in 64 Hz ticks, ~ 15.6 ms apart)

;------------------------------------------------------------------------------
; AUD2_PERIOD_LOW: Audio channel 2 period (low 8 bits) [r/w]
;------------------------------------------------------------------------------
def rAud2PeriodLow equ $ff18

;------------------------------------------------------------------------------
; AUD2_CTL: Audio channel 2 period (high 3 bits) and control
;------------------------------------------------------------------------------
def rAud2Ctl equ $ff19

def BIT_AUD2_CTL_RESET        equ 7 ; 1 = reset ("retrigger") the channel [wo]
    def AUD2_CTL_RESET equ 1 << BIT_AUD2_CTL_RESET

def BIT_AUD2_CTL_LEN_ENABLE   equ 6 ; 1 = reset the channel after the length timer expires [r/w]

def MASK_AUD2_CTL_PERIOD_HIGH equ %00000_111 ; upper 3 bits of the channel's "period"

;------------------------------------------------------------------------------
; AUD3_ENABLE: Audio channel 3 enable
;------------------------------------------------------------------------------
def rAud3Enable equ $ff1a

def BIT_AUD3_ENABLE equ 7 ; whether the channel is active [r/w]
    def AUD3_ENABLE_OFF equ 0 << BIT_AUD3_ENABLE
    def AUD3_ENABLE_ON  equ 1 << BIT_AUD3_ENABLE

;------------------------------------------------------------------------------
; AUD3_LEN: Audio channel 3 length timer [wo]
;------------------------------------------------------------------------------
def rAud3Len equ $ff1b

;------------------------------------------------------------------------------
; AUD3_VOL: Audio channel 3 volume
;------------------------------------------------------------------------------
def rAud3Vol equ $ff1c

def MASK_AUD3_VOLUME equ %0_11_00000 ; volume [r/w]
    def AUD3_VOLUME_MUTE equ %0_00_00000 ; 0%
    def AUD3_VOLUME_100  equ %0_01_00000 ; 100%
    def AUD3_VOLUME_50   equ %0_10_00000 ; 50%
    def AUD3_VOLUME_25   equ %0_11_00000 ; 25%

;------------------------------------------------------------------------------
; AUD3_PERIOD_LOW: Audio channel 3 period (low 8 bits) [r/w]
;------------------------------------------------------------------------------
def rAud3PeriodLow equ $ff1d

;------------------------------------------------------------------------------
; AUD3_CTL: Audio channel 3 period (high 3 bits) and control
;------------------------------------------------------------------------------
def rAud3Ctl equ $ff1e

def BIT_AUD3_CTL_RESET        equ 7 ; 1 = reset ("retrigger") the channel [wo]
    def AUD3_CTL_RESET equ 1 << BIT_AUD3_CTL_RESET

def BIT_AUD3_CTL_LEN_ENABLE   equ 6 ; 1 = reset the channel after the length timer expires [r/w]

def MASK_AUD3_CTL_PERIOD_HIGH equ %00000_111 ; upper 3 bits of the channel's "period"

;------------------------------------------------------------------------------
; $FF1F is unused
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; AUD4_LEN: Audio channel 4 length timer [wo]
;------------------------------------------------------------------------------
def rAud4Len equ $ff20

def MASK_AUD4_LEN_TIMER equ %00_111111 ; initial length timer [r/w]

;------------------------------------------------------------------------------
; AUD4_ENV: Audio channel 4 volume and envelope
;------------------------------------------------------------------------------
def rAud4Env equ $ff21

def MASK_AUD4_INIT_VOL equ %1111_0000 ; initial volume [r/w]

def BIT_AUD4_ENV_DIR   equ 3 ; direction of volume envelope [r/w]
    def MASK_AUD4_ENV_DIR equ 1 << BIT_AUD4_ENV_DIR
        def AUD4_ENV_DOWN equ 0 << BIT_AUD4_ENV_DIR
        def AUD4_ENV_UP   equ 1 << BIT_AUD4_ENV_DIR

def MASK_AUD4_ENV_PACE equ %00000_111 ; how long between envelope iterations [r/w]
                                      ; (in 64 Hz ticks, ~ 15.6 ms apart)

;------------------------------------------------------------------------------
; AUD4_NOISE: Audio channel 4 period and randomness
;------------------------------------------------------------------------------
def rAud4Noise equ $ff22

def MASK_AUD4_NOISE_CLK_SHIFT equ %1111_0000 ; coarse control of the channel's period [r/w]

def BIT_AUD4_NOISE_WIDTH      equ 3 ; controls the noise generator (LFSR)'s "width" [r/w]
    def AUD4_NOISE_15BIT equ 0 << BIT_AUD4_NOISE_WIDTH
    def AUD4_NOISE_7BIT  equ 1 << BIT_AUD4_NOISE_WIDTH

def MASK_AUD4_NOISE_CLK_DIV   equ %00000_111 ; fine control of the channel's period [r/w]

;------------------------------------------------------------------------------
; AUD4_CTL: Audio channel 4 control
;------------------------------------------------------------------------------
def rAud4Ctl equ $ff23

def BIT_AUD4_CTL_RESET      equ 7 ; 1 = reset ("retrigger") the channel [wo]
    def AUD4_CTL_RESET equ 1 << BIT_AUD4_CTL_RESET

def BIT_AUD4_CTL_LEN_ENABLE equ 6 ; 1 = reset the channel after the length timer expires [r/w]

;------------------------------------------------------------------------------
; AUDIO_VOLUME: Audio master volume and VIN mixer
;------------------------------------------------------------------------------
def rAudioVolume equ $ff24

def BIT_AUDIO_VOLUME_VIN_LEFT  equ 7 ; 1 = output VIN to left ear [r/w]
    def MASK_AUDIO_VOLUME_VIN_LEFT equ 1 << BIT_AUDIO_VOLUME_VIN_LEFT
def MASK_AUDIO_VOLUME_LEFT     equ %0_111_0000 ; 0 = barely audible, 7 = full volume [r/w]

def BIT_AUDIO_VOLUME_VIN_RIGHT equ 3 ; 1 = output VIN to right ear [r/w]
    def MASK_AUDIO_VOLUME_VIN_RIGHT equ 1 << BIT_AUDIO_VOLUME_VIN_RIGHT
def MASK_AUDIO_VOLUME_RIGHT    equ %00000_111 ; 0 = barely audible, 7 = full volume [r/w]

;------------------------------------------------------------------------------
; AUDIO_MIX: Audio channel mixer
;------------------------------------------------------------------------------
def rAudioMix equ $ff25

def BIT_AUDIO_MIX_CH4_LEFT  equ 7 ; 1 = output CH4 to left ear   [r/w]
    def MASK_AUDIO_MIX_CH4_LEFT equ 1 << BIT_AUDIO_MIX_CH4_LEFT
def BIT_AUDIO_MIX_CH3_LEFT  equ 6 ; 1 = output CH3 to left ear   [r/w]
    def MASK_AUDIO_MIX_CH3_LEFT equ 1 << BIT_AUDIO_MIX_CH3_LEFT
def BIT_AUDIO_MIX_CH2_LEFT  equ 5 ; 1 = output CH2 to left ear   [r/w]
    def MASK_AUDIO_MIX_CH2_LEFT equ 1 << BIT_AUDIO_MIX_CH2_LEFT
def BIT_AUDIO_MIX_CH1_LEFT  equ 4 ; 1 = output CH1 to left ear   [r/w]
    def MASK_AUDIO_MIX_CH1_LEFT equ 1 << BIT_AUDIO_MIX_CH1_LEFT

def BIT_AUDIO_MIX_CH4_RIGHT equ 3 ; 1 = output CH4 to right ear [r/w]
    def MASK_AUDIO_MIX_CH4_RIGHT equ 1 << BIT_AUDIO_MIX_CH4_RIGHT
def BIT_AUDIO_MIX_CH3_RIGHT equ 2 ; 1 = output CH3 to right ear [r/w]
    def MASK_AUDIO_MIX_CH3_RIGHT equ 1 << BIT_AUDIO_MIX_CH3_RIGHT
def BIT_AUDIO_MIX_CH2_RIGHT equ 1 ; 1 = output CH2 to right ear [r/w]
    def MASK_AUDIO_MIX_CH2_RIGHT equ 1 << BIT_AUDIO_MIX_CH2_RIGHT
def BIT_AUDIO_MIX_CH1_RIGHT equ 0 ; 1 = output CH1 to right ear [r/w]
    def MASK_AUDIO_MIX_CH1_RIGHT equ 1 << BIT_AUDIO_MIX_CH1_RIGHT

;------------------------------------------------------------------------------
; AUDIO_ENABLE: Audio master enable
;------------------------------------------------------------------------------
def rAudEnable equ $ff26

def BIT_AUDIO_ENABLE     equ 7 ; 0 = disable the APU, saving power [r/w]
    def AUDIO_ENABLE_OFF equ 0 << BIT_AUDIO_ENABLE
    def AUDIO_ENABLE_ON  equ 1 << BIT_AUDIO_ENABLE

def BIT_AUDIO_ENABLE_CH4 equ 3 ; 1 = CH4 is running [ro]
    def MASK_AUDIO_ENABLE_CH4 equ 1 << BIT_AUDIO_ENABLE_CH4
def BIT_AUDIO_ENABLE_CH3 equ 2 ; 1 = CH3 is running [ro]
    def MASK_AUDIO_ENABLE_CH3 equ 1 << BIT_AUDIO_ENABLE_CH3
def BIT_AUDIO_ENABLE_CH2 equ 1 ; 1 = CH2 is running [ro]
    def MASK_AUDIO_ENABLE_CH2 equ 1 << BIT_AUDIO_ENABLE_CH2
def BIT_AUDIO_ENABLE_CH1 equ 3 ; 1 = CH1 is running [ro]
    def MASK_AUDIO_ENABLE_CH1 equ 1 << BIT_AUDIO_ENABLE_CH1

;------------------------------------------------------------------------------
; PPU_CTL: Graphics control
;------------------------------------------------------------------------------
def rPPUCtl equ $ff40

def BIT_PPU_CTL_POWER      equ 7 ; whether the PPU (and LCD) are turned on [r/w]
    def PPU_CTL_POWER_OFF equ 0 << BIT_PPU_CTL_POWER
    def PPU_CTL_POWER_ON  equ 1 << BIT_PPU_CTL_POWER

def BIT_PPU_CTL_WINDOW_MAP equ 6 ; whether the Window is enabled [r/w]
    def PPU_CTL_WINDOW_MAP_9800 equ 0 << BIT_PPU_CTL_WINDOW_MAP
    def PPU_CTL_WINDOW_MAP_9C00 equ 1 << BIT_PPU_CTL_WINDOW_MAP

def BIT_PPU_CTL_WINDOW_ENA equ 5 ; which tilemap the Window reads from [r/w]
    def PPU_CTL_WINDOW_OFF equ 0 << BIT_PPU_CTL_WINDOW_ENA
    def PPU_CTL_WINDOW_ON  equ 1 << BIT_PPU_CTL_WINDOW_ENA

def BIT_PPU_CTL_TILES      equ 4 ; which "tile blocks" the BG and Window use [r/w]
    def PPU_CTL_TILES_8800 equ 0 << BIT_PPU_CTL_TILES ; Blocks 2 and 1
    def PPU_CTL_TILES_8000 equ 1 << BIT_PPU_CTL_TILES ; Blocks 0 and 1

def BIT_PPU_CTL_BG_MAP     equ 3 ; which tilemap the BG reads from [r/w]
    def PPU_CTL_BG_MAP_OFF equ 0 << BIT_PPU_CTL_BG_MAP
    def PPU_CTL_BG_MAP_ON  equ 1 << BIT_PPU_CTL_BG_MAP

def BIT_PPU_CTL_OBJ_HEIGHT equ 2 ; how many pixels tall each OBJ is [r/w]
    def PPU_CTL_OBJ_HEIGHT_8  equ 0 << BIT_PPU_CTL_OBJ_HEIGHT
    def PPU_CTL_OBJ_HEIGHT_16 equ 1 << BIT_PPU_CTL_OBJ_HEIGHT

def BIT_PPU_CTL_OBJ_ENA    equ 1 ; whether OBJs are enabled [r/w]
    def PPU_CTL_OBJ_OFF equ 0 << BIT_PPU_CTL_OBJ_ENA
    def PPU_CTL_OBJ_ON  equ 1 << BIT_PPU_CTL_OBJ_ENA

def BIT_PPU_CTL_BG         equ 0 ; (DMG only) whether the BG is enabled [r/w]
    def PPU_CTL_BG_OFF equ 0 << BIT_PPU_CTL_BG
    def PPU_CTL_BG_ON  equ 1 << BIT_PPU_CTL_BG
def BIT_PPU_CTL_PRIO       equ 0 ; (CGB only) whether OBJ-to-BG priority bits are honored [r/w]
    def PPU_CTL_PRIO_IGN equ 0 << BIT_PPU_CTL_BG
    def PPU_CTL_PRIO_ENA equ 1 << BIT_PPU_CTL_BG

;------------------------------------------------------------------------------
; PPU_STATUS: Graphics status and interrupt control
;------------------------------------------------------------------------------
def rPPUStatus equ $ff41

def BIT_PPU_STATUS_INTR_Y_MATCH equ 6 ; 1 = CUR_SCANLINE match triggers the PPU interrupt [r/w]
    def PPU_STATUS_INTR_Y_MATCH_OFF equ 0 << BIT_PPU_STATUS_INTR_Y_MATCH
    def PPU_STATUS_INTR_Y_MATCH_ON  equ 1 << BIT_PPU_STATUS_INTR_Y_MATCH

def BIT_PPU_STATUS_INTR_OAM     equ 5 ; 1 = OAM Scan triggers the PPU interrupt [r/w]
    def PPU_STATUS_INTR_OAM_OFF equ 0 << BIT_PPU_STATUS_INTR_OAM
    def PPU_STATUS_INTR_OAM_ON  equ 1 << BIT_PPU_STATUS_INTR_OAM

def BIT_PPU_STATUS_INTR_VBLANK  equ 4 ; 1 = VBlank triggers the PPU interrupt [r/w]
    def PPU_STATUS_INTR_VBLANK_OFF equ 0 << BIT_PPU_STATUS_INTR_VBLANK
    def PPU_STATUS_INTR_VBLANK_ON  equ 1 << BIT_PPU_STATUS_INTR_VBLANK

def BIT_PPU_STATUS_INTR_HBLANK  equ 3 ; 1 = HBlank triggers the PPU interrupt [r/w]
    def PPU_STATUS_INTR_HBLANK_OFF equ 0 << BIT_PPU_STATUS_INTR_HBLANK
    def PPU_STATUS_INTR_HBLANK_ON  equ 1 << BIT_PPU_STATUS_INTR_HBLANK

def BIT_PPU_STATUS_Y_MATCH      equ 2 ; 1 = CUR_SCANLINE is currently equal to SCANLINE_CMP [ro]
    def MASK_PPU_STATUS_Y_MATCH equ 1 << BIT_PPU_STATUS_Y_MATCH

def MASK_PPU_STATUS_MODE equ %000000_11 ; PPU's current status [ro]
    def PPU_STATUS_MODE_HBLANK    equ %000000_00 ; Waiting after a line's rendering
    def PPU_STATUS_MODE_VBLANK    equ %000000_01 ; Waiting between frames
    def PPU_STATUS_MODE_OAM_SCAN  equ %000000_10 ; Checking which OBJs will be rendered on this line
    def PPU_STATUS_MODE_RENDERING equ %000000_11 ; Pushing pixels to the LCD
        def MASK_PPU_STATUS_MODE_BUSY equ %000000_1_0 ; Indicates that the PPU is currently busy

;------------------------------------------------------------------------------
; SCROLL_Y: Background Y scroll offset (in pixels) [r/w]
;------------------------------------------------------------------------------
def rScrollY equ $ff42

;------------------------------------------------------------------------------
; SCROLL_X: Background X scroll offset (in pixels) [r/w]
;------------------------------------------------------------------------------
def rScrollX equ $ff43

;------------------------------------------------------------------------------
; CUR_SCANLINE: Y coordinate of the line currently processed by the PPU [ro]
;------------------------------------------------------------------------------
def rCurScanline equ $ff44

;------------------------------------------------------------------------------
; SCANLINE_CMP: Value that CUR_SCANLINE is constantly compared to [r/w]
;------------------------------------------------------------------------------
def rScanlineCmp equ $ff45

;------------------------------------------------------------------------------
; OAM_DMA: OAM DMA start address (high 8 bits) and start [wo]
;------------------------------------------------------------------------------
def rOamDma equ $ff46

;------------------------------------------------------------------------------
; BG_PALETTE: (DMG only) Background color mapping [r/w]
;------------------------------------------------------------------------------
def rBgPalette equ $ff47

;------------------------------------------------------------------------------
; OBJ_PALETTE0: (DMG only) OBJ color mapping #0 [r/w]
;------------------------------------------------------------------------------
def rObjPalette0 equ $ff48

;------------------------------------------------------------------------------
; OBJ_PALETTE1: (DMG only) OBJ color mapping #1 [r/w]
;------------------------------------------------------------------------------
def rObjPalette1 equ $ff49

;------------------------------------------------------------------------------
; WIN_Y_COORD: Y coordinate of the Window's top-left pixel [r/w]
;------------------------------------------------------------------------------
def rWinYCoord equ $ff4a

;------------------------------------------------------------------------------
; WIN_X_COORD: X coordinate of the Window's top-left pixel (plus 7) [r/w]
;------------------------------------------------------------------------------
def rWinXCoord equ $ff4b

def WIN_X_COORD_OFFSET equ 7 ; Subtract this to get the actual Window Y coordinate

;------------------------------------------------------------------------------
; SYS_CTL: (CGB boot ROM only) System mode
;------------------------------------------------------------------------------
def rSysCtl equ $ff4c

def MASK_SYS_CTL_MODE equ %0000_11_00 ; current system mode [r/w]
    def SYS_CTL_MODE_CGB  equ %0000_00_00 ; CGB mode
    def SYS_CTL_MODE_DMG  equ %0000_01_00 ; DMG compatibility mode
    def SYS_CTL_MODE_PGB1 equ %0000_10_00 ; LCD is driven externally, CPU is stopped
    def SYS_CTL_MODE_PGB2 equ %0000_11_00 ; LCD is driven externally, CPU is running

;------------------------------------------------------------------------------
; CLOCK_CTL: (CGB only) Double-speed mode control
;------------------------------------------------------------------------------
def rClockCtl equ $ff4d

def BIT_CLOCK_CTL_SPEED equ 7 ; current clock speed [ro]
    def CLOCK_CTL_SPEED_NORMAL equ 0 << BIT_CLOCK_CTL_SPEED
    def CLOCK_CTL_SPEED_DOUBLE equ 1 << BIT_CLOCK_CTL_SPEED

def BIT_CLOCK_CTL_ARMED equ 0 ; 1 = next `stop` instruction will switch clock speeds
def CLOCK_CTL_ARM_SWITCH equ 1 << BIT_CLOCK_CTL_ARMED

;------------------------------------------------------------------------------
; $FF4E is unused
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; VRAM_BANK: (CGB only) VRAM bank number
;------------------------------------------------------------------------------
def rVramBank equ $ff4f

def MASK_VRAM_BANK equ %0000000_1 ; mapped VRAM bank [r/w]

;------------------------------------------------------------------------------
; BOOT_ROM_CTL: (boot ROM only) Boot ROM mapping control
;------------------------------------------------------------------------------
def rBootRomCtl equ $ff50

def BIT_BOOT_ROM_CTL_MAPPING equ 0 ; whether the boot ROM is mapped [wo]
    def BOOT_ROM_CTL_MAPPING_ON  equ 0 << BIT_BOOT_ROM_CTL_MAPPING
    def BOOT_ROM_CTL_MAPPING_OFF equ 1 << BIT_BOOT_ROM_CTL_MAPPING

;------------------------------------------------------------------------------
; VDMA_SRC_HIGH: (CGB only) VRAM DMA source address (high 8 bits) [wo]
;------------------------------------------------------------------------------
def rVDMASrcHigh equ $ff51

;------------------------------------------------------------------------------
; VDMA_SRC_LOW: (CGB only) VRAM DMA source address (low 8 bits) [wo]
;------------------------------------------------------------------------------
def rVDMASrcLow equ $ff52

;------------------------------------------------------------------------------
; VDMA_DEST_HIGH: (CGB only) VRAM DMA destination address (high 8 bits) [wo]
;------------------------------------------------------------------------------
def rVDMADestHigh equ $ff53

;------------------------------------------------------------------------------
; VDMA_DEST_LOW: (CGB only) VRAM DMA destination address (low 8 bits) [wo]
;------------------------------------------------------------------------------
def rVDMADestLow equ $ff54

;------------------------------------------------------------------------------
; VDMA_LEN: (CGB only) VRAM DMA length, mode, and start
;------------------------------------------------------------------------------
def rVDMALen equ $ff55

def BIT_VDMA_LEN_MODE   equ 7 ; on write: VRAM DMA mode
    def VDMA_LEN_MODE_GDMA equ 0 << BIT_VDMA_LEN_MODE
    def VDMA_LEN_MODE_HDMA equ 1 << BIT_VDMA_LEN_MODE
def BIT_VDMA_LEN_ACTIVE equ 7 ; on read: is a VRAM DMA active?
    def MASK_VDMA_LEN_ACTIVE equ 1 << BIT_VDMA_LEN_ACTIVE ; 0 = a VRAM DMA is active

def MASK_VDMA_LEN_SIZE equ %0_1111111 ; how many 16-byte blocks to transfer [r/w]

;------------------------------------------------------------------------------
; IR_CTL: (CGB only) Infrared port control
;------------------------------------------------------------------------------
def rIRCtl equ $ff56

def MASK_IR_CTL_READ_ENABLE equ %11_000000 ; whether the IR read is enabled [r/w]
    def IR_CTL_READ_ENABLED equ %11_000000 ; IR_CTL_READ will read 1 until this is written

def BIT_IR_CTL_RECV equ 1 ; whether IR light is being received [ro]
    def MASK_IR_CTL_RECV equ 1 << BIT_IR_CTL_RECV

def BIT_IR_CTL_SEND equ 0 ; whether IR light is being sent [r/w]
    def MASK_IR_CTL_SEND equ 1 << BIT_IR_CTL_SEND

;------------------------------------------------------------------------------
; $FF57-$FF67 are unused
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; BG_PAL_ADDR: (CGB only) Background palette I/O address
;------------------------------------------------------------------------------
def rBgPalAddr equ $ff68

def BIT_BG_PAL_ADDR_AUTOINC equ 7 ; whether the address field is incremented after
                                  ; each **write** to BG_PAL_DATA [r/w]
    def BG_PAL_ADDR_AUTOINC equ 1 << BIT_BG_PAL_ADDR_AUTOINC

def MASK_BG_PAL_ADDR equ %00_111111 ; the address within Palette RAM accessed via BG_PAL_DATA [r/w]

;------------------------------------------------------------------------------
; BG_PAL_DATA: (CGB only) Background palette I/O access [r/w]
;------------------------------------------------------------------------------
def rBgPalData equ $ff69

;------------------------------------------------------------------------------
; OBJ_PAL_ADDR: (CGB only) OBJ palette I/O address
;------------------------------------------------------------------------------
def rObjPalAddr equ $ff6a

def BIT_OBJ_PAL_ADDR_AUTOINC equ 7 ; whether the address field is incremented after
                                   ; each **write** to OBJ_PAL_DATA [r/w]
    def OBJ_PAL_ADDR_AUTOINC equ 1 << BIT_OBJ_PAL_ADDR_AUTOINC

    def MASK_OBJ_PAL_ADDR equ %00_111111 ; the address within Palette RAM accessed
                                         ; via OBJ_PAL_DATA [r/w]

;------------------------------------------------------------------------------
; OBJ_PAL_DATA: (CGB only) OBJ palette I/O access [r/w]
;------------------------------------------------------------------------------
def rObjPalData equ $ff6b

;------------------------------------------------------------------------------
; OBJ_DRAW_PRIO: (CGB boot ROM only)
;------------------------------------------------------------------------------
def rObjDrawPrio equ $ff6c

def BIT_OBJ_DRAW_PRIO equ 0 ; which drawing priority is used for OBJs [r/w]
    def OBJ_DRAW_PRIO_OAM   equ 0 << BIT_OBJ_DRAW_PRIO ; CGB priority: earliest OBJ in OAM wins
    def OBJ_DRAW_PRIO_COORD equ 1 << BIT_OBJ_DRAW_PRIO ; DMG priority: leftmost OBJ wins

;------------------------------------------------------------------------------
; $FF6D-$FF6F are unused
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; WRAM_BANK: (CGB only) WRAM bank number
;------------------------------------------------------------------------------
def rWramBank equ $ff70

def MASK_WRAM_BANK equ %00000_111 ; mapped WRAM bank [r/w]

;------------------------------------------------------------------------------
; $FF71-$FF75 are unused
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; AUD_OUT12: (CGB only) Audio channels 1 and 2 output
;------------------------------------------------------------------------------
def rAudOut12 equ $ff76

def MASK_AUD_OUT12_CH2 equ %1111_0000 ; audio channel 2 output
def MASK_AUD_OUT12_CH1 equ %0000_1111 ; audio channel 1 output

;------------------------------------------------------------------------------
; AUD_OUT34: (CGB only) Audio channels 3 and 4 output
;------------------------------------------------------------------------------
def rAudOut34 equ $ff77

def MASK_AUD_OUT34_CH4 equ %1111_0000 ; audio channel 4 output
def MASK_AUD_OUT34_CH3 equ %0000_1111 ; audio channel 3 output

;------------------------------------------------------------------------------
; $FF78-$FF7F are unused
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; INTR_ENABLED: Pending interrupts
;------------------------------------------------------------------------------
def rIntrEnabled equ $ffff

def BIT_INTR_ENABLED_JOYPAD   equ 4 ; 1 = Joypad interrupt is enabled [r/w]
    def MASK_INTR_ENABLED_JOYPAD equ 1 << BIT_INTR_ENABLED_JOYPAD
    def rINTR_ENABLED_JOYPAD_OFF equ 0 << BIT_INTR_ENABLED_JOYPAD
    def rINTR_ENABLED_JOYPAD_ON  equ 1 << BIT_INTR_ENABLED_JOYPAD

    def BIT_INTR_ENABLED_SERIAL equ 3 ; 1 = Serial interrupt is enabled [r/w]
    def MASK_INTR_ENABLED_SERIAL equ 1 << BIT_INTR_ENABLED_SERIAL
    def rINTR_ENABLED_SERIAL_OFF equ 0 << BIT_INTR_ENABLED_SERIAL
    def rINTR_ENABLED_SERIAL_ON  equ 1 << BIT_INTR_ENABLED_SERIAL

    def BIT_INTR_ENABLED_TIMER  equ 2 ; 1 =  Timer interrupt is enabled [r/w]
    def MASK_INTR_ENABLED_TIMER equ 1 << BIT_INTR_ENABLED_TIMER
    def rINTR_ENABLED_TIMER_OFF equ 0 << BIT_INTR_ENABLED_TIMER
    def rINTR_ENABLED_TIMER_ON  equ 1 << BIT_INTR_ENABLED_TIMER

    def BIT_INTR_ENABLED_PPU    equ 1 ; 1 =    PPU interrupt is enabled [r/w]
    def MASK_INTR_ENABLED_PPU equ 1 << BIT_INTR_ENABLED_PPU
    def rINTR_ENABLED_PPU_OFF equ 0 << BIT_INTR_ENABLED_PPU
    def rINTR_ENABLED_PPU_ON  equ 1 << BIT_INTR_ENABLED_PPU

    def BIT_INTR_ENABLED_VBLANK equ 0 ; 1 = VBlank interrupt is enabled [r/w]
    def MASK_INTR_ENABLED_VBLANK equ 1 << BIT_INTR_ENABLED_VBLANK
    def rINTR_ENABLED_VBLANK_OFF equ 0 << BIT_INTR_ENABLED_VBLANK
    def rINTR_ENABLED_VBLANK_ON  equ 1 << BIT_INTR_ENABLED_VBLANK

; TODO: MBC registers

endc ; def(HARDWARE_INC)
