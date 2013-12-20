#poke_crunch_function_generator_white_noise_58==================================================================================1

level = inputs[0].value_get()
mute = inputs[1].value_get()
property = {  'scale_factor':'1','available_mips':'115','block_size':'16','chip_required':'49600','clip_hold_time':'1','compile_debug':'0','external_mem_address':'0','external_mem_enabled':'false','external_mem_size':'0','firmware_version':'<current>','overlay':'cc','pacman_poll_rate':'10','ramp_time_constant':'0.075','sample_rate':'48000','target_dsp':'all','x_heap_size':'0','x_memory_size':'2000','y_heap_size':'0','y_memory_size':'8000' }

# python function for crunching input control values
#   
#message.string_set( "bypass = %d, gain = %f, invert = %d, mute = %f, scale = %f" % (bypass, gain, invert, mute, scale ))

sample_rate = int( property[ "sample_rate"] ) # global sample_rate
block_size = int( property[ "block_size"] )   # global block size
block_rate = sample_rate / block_size         # global block rate
ramp_time_constant = float( property[ "ramp_time_constant" ] )
ramp = 1 - math.exp( -1 / ( ramp_time_constant * block_rate ) )

if( mute ):
  gain = 0
else:
  # peak-to-RMS ratio of white noise is equal to 4.77 dB
  gain = math.pow( 10, ( level - ( 20.0 + 3.0103 - 4.77 ) ) / 20 ) / 16

    
poke_list = [[ramp,31,1],[gain,31,1]]
dsp.poke_multiple( 0x1, 0, poke_list )

#poke_crunch_function_meter_N_true_peak_and_RMS_113==================================================================================2
infinite_peak_hold = inputs[0].value_get()
peak_decay_time = inputs[1].value_get()
peak_hold_time = inputs[2].value_get()
rms_response_time = inputs[3].value_get()
property = {  'input_count':'1','deep_mode':'1','scale_factor':'1','available_mips':'115','block_size':'16','chip_required':'49600','clip_hold_time':'1','compile_debug':'0','external_mem_address':'0','external_mem_enabled':'false','external_mem_size':'0','firmware_version':'<current>','overlay':'cc','pacman_poll_rate':'10','ramp_time_constant':'0.075','sample_rate':'48000','target_dsp':'all','x_heap_size':'0','x_memory_size':'2000','y_heap_size':'0','y_memory_size':'8000' }

# python function for crunching input control values

scale_factor = float( property[ "scale_factor" ] )
sample_rate = float( property[ "sample_rate" ] ) * scale_factor
block_size = float( property[ "block_size" ] ) * scale_factor

block_rate = sample_rate / block_size

# compute RMS response filter coefficient
b = math.tan( ( 1.0 / ( block_rate * rms_response_time ) ) / 2 )
coeff_rms = 1 - ( 1 - b ) / ( 1 + b )

# compute peak decay filter coefficient
b = math.tan( ( 1.0 / ( block_rate * peak_decay_time ) ) / 2 )
coeff_peak = ( 1 - b ) / ( 1 + b )

hold_count = peak_hold_time * block_rate

#message.string_set( "coeff_rms = " + str( coeff_rms ) )
#message.string_set( "coeff_peak = " + str( coeff_peak ) )
#message.string_set( "hold_count = " + str( hold_count ) )
#message.string_set( "infinite_peak_hold = " + str( infinite_peak_hold ) )

	  
poke_list = [[coeff_rms,31,1],[coeff_peak,31,1],[hold_count,0,1],[infinite_peak_hold,0,1]]
dsp.poke_multiple( 0x1, 2, poke_list )

#peek_crunch_function_meter_N_true_peak_and_RMS_113==================================================================================3
ms_1 = dsp.peek(0x0,3,31,1)
ms_hold_1 = dsp.peek(0x0,5,31,1)
pk_1 = dsp.peek(0x0,4,31,1)
pk_hold_1 = dsp.peek(0x0,6,31,1)
property = {  'input_count':'1','deep_mode':'1','scale_factor':'1','available_mips':'115','block_size':'16','chip_required':'49600','clip_hold_time':'1','compile_debug':'0','external_mem_address':'0','external_mem_enabled':'false','external_mem_size':'0','firmware_version':'<current>','overlay':'cc','pacman_poll_rate':'10','ramp_time_constant':'0.075','sample_rate':'48000','target_dsp':'all','x_heap_size':'0','x_memory_size':'2000','y_heap_size':'0','y_memory_size':'8000' }

# python function for crunching read-only output control values

offset = 20 + 10 * math.log10( 2 ) + 20 * math.log10( 16 )
n = int( property[ "input_count"] )
for i in range(1,n+1):
  exec "ms = ms_" + str(i);
  if ms > ( 0.000001 * 0.000001 ) :
    rms = offset + 10 * math.log10( ms )
  else :
    rms = -100
  exec "rms_" + str(i) + " = rms"

  exec "ms_hold = ms_hold_" + str(i)
  if ms_hold > ( 0.000001 * 0.000001 ) :
    rms_hold = offset + 10 * math.log10( ms_hold )
  else :
    rms_hold = -100
  exec "rms_hold_" + str(i) + " = rms_hold"

  exec "pk = pk_" + str(i)
  if pk > 0.000001 :
    peak = offset + 20 * math.log10( pk )
  else :
    peak = -100
  exec "peak_" + str(i) + " = peak"

  exec "pk_hold = pk_hold_" + str(i)
  if pk_hold > 0.000001 :
    peak_hold = offset + 20 * math.log10( pk_hold )
  else :
    peak_hold = -100
  exec "peak_hold_" + str(i) + " = peak_hold"

  #message.string_set( "ms = " + str( ms ) )
  #message.string_set( "rms = " + str( rms ) )
  #message.string_set( "pk = " + str( pk ) )
  #message.string_set( "peak = " + str( peak ) )

	  
outputs[0].value_set(peak_1)
outputs[1].value_set(peak_hold_1)
outputs[2].value_set(rms_1)
outputs[3].value_set(rms_hold_1)

#poke_crunch_function_gain_78==================================================================================4
gain = inputs[0].value_get()
invert = inputs[1].value_get()
mute = inputs[2].value_get()
property = {  'scale_factor':'1','available_mips':'115','block_size':'16','chip_required':'49600','clip_hold_time':'1','compile_debug':'0','external_mem_address':'0','external_mem_enabled':'false','external_mem_size':'0','firmware_version':'<current>','overlay':'cc','pacman_poll_rate':'10','ramp_time_constant':'0.075','sample_rate':'48000','target_dsp':'all','x_heap_size':'0','x_memory_size':'2000','y_heap_size':'0','y_memory_size':'8000' }

# python function for crunching input control values

scale_factor = float( property[ "scale_factor" ] )
sample_rate = float( property[ "sample_rate" ] ) * scale_factor
block_size = float( property[ "block_size" ] ) * scale_factor
ramp_time_constant = float( property[ "ramp_time_constant" ] )
clip_hold_time = float( property[ "clip_hold_time" ] )

block_rate = sample_rate / block_size
ramp = 1 - math.exp( -1 / ( ramp_time_constant * block_rate ) )
hold_count = clip_hold_time * block_rate

g = math.pow( 10, gain / 20 )

if mute or gain <= -100 :
  g = 0

if invert :
  g = -g

#message.string_set( "ramp = " + str( ramp ) )
#message.string_set( "hold_count = " + str( hold_count ) )
#message.string_set( "g = " + str( g ) )

	  
poke_list = [[ramp,31,1],[g,29,1],[hold_count,0,1]]
dsp.poke_multiple( 0x1, 6, poke_list )

#peek_crunch_function_gain_78==================================================================================5
clip = dsp.peek(0x0,7,0,1)
property = {  'scale_factor':'1','available_mips':'115','block_size':'16','chip_required':'49600','clip_hold_time':'1','compile_debug':'0','external_mem_address':'0','external_mem_enabled':'false','external_mem_size':'0','firmware_version':'<current>','overlay':'cc','pacman_poll_rate':'10','ramp_time_constant':'0.075','sample_rate':'48000','target_dsp':'all','x_heap_size':'0','x_memory_size':'2000','y_heap_size':'0','y_memory_size':'8000' }

# python function for crunching read-only output control values

#message.string_set( "clip = " + str( clip ) )

	  
outputs[0].value_set(clip)

#poke_crunch_function_router_NxM_basic_59==================================================================================6
output_mute_1 = inputs[0].value_get()
output_select_1 = inputs[1].value_get()
property = {  'input_count':'5','output_count':'1','scale_factor':'1','available_mips':'115','block_size':'16','chip_required':'49600','clip_hold_time':'1','compile_debug':'0','external_mem_address':'0','external_mem_enabled':'false','external_mem_size':'0','firmware_version':'<current>','overlay':'cc','pacman_poll_rate':'10','ramp_time_constant':'0.075','sample_rate':'48000','target_dsp':'all','x_heap_size':'0','x_memory_size':'2000','y_heap_size':'0','y_memory_size':'8000' }

# python function for crunching input control values

sample_rate = int( property[ "sample_rate"] ) # global sample_rate
block_size = int( property[ "block_size"] )   # global block size
block_rate = sample_rate / block_size         # global block rate
ramp_time_constant = float( property[ "ramp_time_constant" ] )
ramp = 1 - math.exp( -1 / ( ramp_time_constant * block_rate ) )

input_count = int( property["input_count"] )
output_count = int( property["output_count"] )
for i in range(output_count):
  if( eval( "output_mute_%d" % (i+1) ) == 1 ):
    exec "output_select_%d = 0" % ( i+1 )
  else:
    exec "output_select_%d = output_select_%d" % ( i+1, i+1 )
  #message.string_set( "output_select_%d = %f " % ( i+1, eval("output_select_%d"%(i+1)) ) )
    
poke_list = [[ramp,31,1],[output_select_1,0,1]]
dsp.poke_multiple( 0x1, 15, poke_list )

#poke_crunch_function_gain_down_24dB_multi_channel_217==================================================================================7
channel_gain_1 = inputs[0].value_get()
channel_gain_10 = inputs[1].value_get()
channel_gain_11 = inputs[2].value_get()
channel_gain_12 = inputs[3].value_get()
channel_gain_13 = inputs[4].value_get()
channel_gain_14 = inputs[5].value_get()
channel_gain_15 = inputs[6].value_get()
channel_gain_16 = inputs[7].value_get()
channel_gain_2 = inputs[8].value_get()
channel_gain_3 = inputs[9].value_get()
channel_gain_4 = inputs[10].value_get()
channel_gain_5 = inputs[11].value_get()
channel_gain_6 = inputs[12].value_get()
channel_gain_7 = inputs[13].value_get()
channel_gain_8 = inputs[14].value_get()
channel_gain_9 = inputs[15].value_get()
channel_invert_1 = inputs[16].value_get()
channel_invert_10 = inputs[17].value_get()
channel_invert_11 = inputs[18].value_get()
channel_invert_12 = inputs[19].value_get()
channel_invert_13 = inputs[20].value_get()
channel_invert_14 = inputs[21].value_get()
channel_invert_15 = inputs[22].value_get()
channel_invert_16 = inputs[23].value_get()
channel_invert_2 = inputs[24].value_get()
channel_invert_3 = inputs[25].value_get()
channel_invert_4 = inputs[26].value_get()
channel_invert_5 = inputs[27].value_get()
channel_invert_6 = inputs[28].value_get()
channel_invert_7 = inputs[29].value_get()
channel_invert_8 = inputs[30].value_get()
channel_invert_9 = inputs[31].value_get()
channel_mute_1 = inputs[32].value_get()
channel_mute_10 = inputs[33].value_get()
channel_mute_11 = inputs[34].value_get()
channel_mute_12 = inputs[35].value_get()
channel_mute_13 = inputs[36].value_get()
channel_mute_14 = inputs[37].value_get()
channel_mute_15 = inputs[38].value_get()
channel_mute_16 = inputs[39].value_get()
channel_mute_2 = inputs[40].value_get()
channel_mute_3 = inputs[41].value_get()
channel_mute_4 = inputs[42].value_get()
channel_mute_5 = inputs[43].value_get()
channel_mute_6 = inputs[44].value_get()
channel_mute_7 = inputs[45].value_get()
channel_mute_8 = inputs[46].value_get()
channel_mute_9 = inputs[47].value_get()
property = {  'channel_count':'16','scale_factor':'1','available_mips':'115','block_size':'16','chip_required':'49600','clip_hold_time':'1','compile_debug':'0','external_mem_address':'0','external_mem_enabled':'false','external_mem_size':'0','firmware_version':'<current>','overlay':'cc','pacman_poll_rate':'10','ramp_time_constant':'0.075','sample_rate':'48000','target_dsp':'all','x_heap_size':'0','x_memory_size':'2000','y_heap_size':'0','y_memory_size':'8000' }

# python function for crunching input control values

scale_factor = float( property[ "scale_factor" ] )
sample_rate = float( property[ "sample_rate" ] ) * scale_factor
block_size = float( property[ "block_size" ] ) * scale_factor
ramp_time_constant = float( property[ "ramp_time_constant" ] )
channel_count = int( property[ "channel_count"] )

block_rate = sample_rate / block_size
ramp = 1 - math.exp( -1 / ( ramp_time_constant * block_rate ) )

#message.string_set( "ramp = " + str( ramp ) )

channel_mute = [0] * channel_count
channel_invert = [1] * channel_count
channel_gain = [0] * channel_count

for i in range( channel_count ) :
  channel_mute[ i ] = not eval( "channel_mute_" + str( i + 1 ) )
  if( eval( "channel_invert_" + str( i + 1) ) ) : channel_invert[ i ] = -1
  channel_gain[ i ] = math.pow( 10, eval( "channel_gain_" + str( i + 1 ) ) / 20 )
  if eval( "channel_gain_" + str( i + 1 ) ) <= -100 : channel_gain[ i ] = 0

# gain[i]  = channel_mute[i] * channel_invert[i] * channel_gain[i]

for i in range( channel_count ) :
  # divide gain by 16 to provide for approximately 24dB of digital headroom
  g = channel_mute[ i ] * channel_invert[ i ] * channel_gain[ i ] / 16
  exec "g_%d = %f" % ( i + 1, g )
#  message.string_set( "g_%d = %f" % ( i + 1, g ) )

	  
poke_list = [[ramp,31,1],[g_1,31,1],[g_2,31,1],[g_3,31,1],[g_4,31,1],[g_5,31,1],[g_6,31,1],[g_7,31,1],[g_8,31,1],[g_9,31,1],[g_10,31,1],[g_11,31,1],[g_12,31,1],[g_13,31,1],[g_14,31,1],[g_15,31,1],[g_16,31,1]]
dsp.poke_multiple( 0x1, 21, poke_list )

#poke_crunch_function_detector_peak_square_267==================================================================================8
input_disable_1 = inputs[0].value_get()
time_constant = inputs[1].value_get()
property = {  'input_count':'1','scale_factor':'1','available_mips':'115','block_size':'16','chip_required':'49600','clip_hold_time':'1','compile_debug':'0','external_mem_address':'0','external_mem_enabled':'false','external_mem_size':'0','firmware_version':'<current>','overlay':'cc','pacman_poll_rate':'10','ramp_time_constant':'0.075','sample_rate':'48000','target_dsp':'all','x_heap_size':'0','x_memory_size':'2000','y_heap_size':'0','y_memory_size':'8000' }

# python function for crunching input control values
#   
#message.string_set( "bypass = %d, gain = %f, invert = %d, mute = %f, scale = %f" % (bypass, gain, invert, mute, scale ))

sample_rate = int( property[ "sample_rate"] ) # global sample_rate
block_size = int( property[ "block_size"] )   # global block size
block_rate = sample_rate / block_size         # global block rate

tc = 1 - math.exp( -1 / ( time_constant * block_rate ) )
#message.string_set( "time_constant = %f, input_disable_1 = %d" % ( time_constant, input_disable_1 ) )
#message.string_set( "tc = " + str( tc ) )

    
poke_list = [[input_disable_1,0,1],[tc,31,1]]
dsp.poke_multiple( 0x1, 64, poke_list )

#peek_crunch_function_detector_peak_square_267==================================================================================9
max_peak = dsp.peek(0x0,16,31,1)
property = {  'input_count':'1','scale_factor':'1','available_mips':'115','block_size':'16','chip_required':'49600','clip_hold_time':'1','compile_debug':'0','external_mem_address':'0','external_mem_enabled':'false','external_mem_size':'0','firmware_version':'<current>','overlay':'cc','pacman_poll_rate':'10','ramp_time_constant':'0.075','sample_rate':'48000','target_dsp':'all','x_heap_size':'0','x_memory_size':'2000','y_heap_size':'0','y_memory_size':'8000' }

# python function for crunching read-only control values
headroom = 20 + 10 * math.log10( 2 ) + 20 * math.log10( 16 )
if max_peak == 0:
  max_peak = 2**(-31)
maximum_level = headroom + 20*math.log10( max_peak )

    
outputs[0].value_set(maximum_level)

#poke_crunch_function_dynamic_gate_zero_cross_268==================================================================================10
bypass = inputs[0].value_get()
depth = inputs[1].value_get()
hold_time = inputs[2].value_get()
threshold = inputs[3].value_get()
property = {  'channel_count':'1','scale_factor':'1','available_mips':'115','block_size':'16','chip_required':'49600','clip_hold_time':'1','compile_debug':'0','external_mem_address':'0','external_mem_enabled':'false','external_mem_size':'0','firmware_version':'<current>','overlay':'cc','pacman_poll_rate':'10','ramp_time_constant':'0.075','sample_rate':'48000','target_dsp':'all','x_heap_size':'0','x_memory_size':'2000','y_heap_size':'0','y_memory_size':'8000' }

# python function for crunching input control values
#   
#message.string_set( "bypass = %d, gain = %f, invert = %d, mute = %f, scale = %f" % (bypass, gain, invert, mute, scale ))
sample_rate = int( property[ "sample_rate" ] ) # global sample_rate
block_size = int( property[ "block_size" ] )   # global block size
block_rate = sample_rate / block_size         # global block rate

dsp_depth = -math.pow( 10, depth/20 )    # use negtive gain
dsp_hold_time = hold_time * block_rate
dsp_bypass = bypass

    
poke_list = [[threshold,23,1],[dsp_hold_time,0,1],[dsp_depth,31,1],[dsp_bypass,0,1]]
dsp.poke_multiple( 0x1, 66, poke_list )

#peek_crunch_function_dynamic_gate_zero_cross_268==================================================================================11
dsp_open = dsp.peek(0x0,17,0,1)
property = {  'channel_count':'1','scale_factor':'1','available_mips':'115','block_size':'16','chip_required':'49600','clip_hold_time':'1','compile_debug':'0','external_mem_address':'0','external_mem_enabled':'false','external_mem_size':'0','firmware_version':'<current>','overlay':'cc','pacman_poll_rate':'10','ramp_time_constant':'0.075','sample_rate':'48000','target_dsp':'all','x_heap_size':'0','x_memory_size':'2000','y_heap_size':'0','y_memory_size':'8000' }

# python function for crunching read-only control values
#message.string_set( "dsp_reduction = %f" % (dsp_reduction))
open = dsp_open
    
outputs[0].value_set(open)



#poke_crunch_function_filter_highpass_transposed_direct_II_64==================================================================================12
bypass = inputs[0].value_get()
frequency = inputs[1].value_get()
gain = inputs[2].value_get()
invert = inputs[3].value_get()
mute = inputs[4].value_get()
normalization = inputs[5].value_get()
order = inputs[6].value_get()
q_factor = inputs[7].value_get()
type = inputs[8].value_get()
property = {  'max_order':'2','low_pass':'0','scale_factor':'1','available_mips':'115','block_size':'16','chip_required':'49600','clip_hold_time':'1','compile_debug':'0','external_mem_address':'0','external_mem_enabled':'false','external_mem_size':'0','firmware_version':'<current>','overlay':'cc','pacman_poll_rate':'10','ramp_time_constant':'0.075','sample_rate':'48000','target_dsp':'all','x_heap_size':'0','x_memory_size':'2000','y_heap_size':'0','y_memory_size':'8000' }

# python function for crunching input control values

scale_factor = float( property[ "scale_factor" ] )
sample_rate = float( property[ "sample_rate" ] ) * scale_factor
block_size = float( property[ "block_size" ] ) * scale_factor
ramp_time_constant = float( property[ "ramp_time_constant" ] )
clip_hold_time = float( property[ "clip_hold_time" ] )
max_order = int( property[ "max_order" ] )
low_pass = int( property[ "low_pass" ] )

block_rate = sample_rate / block_size
ramp = 1 - math.exp( -1 / ( ramp_time_constant * block_rate ) )
hold_count = clip_hold_time * block_rate
max_biquad = ( max_order + 1 ) / 2

#message.string_set( "ramp = " + str( ramp ) )
#message.string_set( "hold_count = " + str( hold_count ) )

# Bessel second order section damping scale factors (filter order: 0, 1, 2, 3, etc.)
#     1st section   2nd section   3rd section   4th section
#     -----------------------------------------------------
bessel_damping = \
  [ \
    [ 0,            0,            0,            0,           ], \
    [ 1,            0,            0,            0,           ], \
    [ 1.7320508076, 0,            0,            0,           ], \
    [ 1.4470803599, 0,            0,            0,           ], \
    [ 1.9159489237, 1.2414059301, 0,            0,           ], \
    [ 1.7745107195, 1.0911344114, 0,            0,           ], \
    [ 1.9595631418, 1.6361402521, 0.9772172032, 0,           ], \
    [ 1.8784433114, 1.5132682086, 0.8878963849, 0,           ], \
    [ 1.9763194659, 1.7869614419, 1.4067624418, 0.8158806765 ] \
  ]

# Bessel second order section frequency scale factors (filter order: 0, 1, 2, 3, etc.)
#     1st section   2nd section   3rd section   4th section
#     -----------------------------------------------------
bessel_frequency = \
  [ \
    [ 0,            0,            0,            0,           ], \
    [ 1,            0,            0,            0,           ], \
    [ 1.7320508076, 0,            0,            0,           ], \
    [ 2.5415414011, 0,            0,            0,           ], \
    [ 3.0232649388, 3.3893657927, 0,            0,           ], \
    [ 3.7778936609, 4.2610228013, 0,            0,           ], \
    [ 4.3360270513, 4.5664891522, 5.1491771521, 0,           ], \
    [ 5.0662061498, 5.3792700335, 6.0495276805, 0,           ], \
    [ 5.6548408694, 5.8253532155, 6.2104149036, 6.9593116508 ] \
  ]

# Bessel first order section frequency scale factors (filter order: 1, 3, 5, 7, etc.)
bessel_frequency_first_order = \
  [ \
    1, \
    2.3221853546, \
    3.6467385953, \
    4.9717868586 \
  ]

# Bessel phase match cut-off frequency normalization factors (filter order: 0, 1, 2, 3, etc.)
bessel_normalization_phase_match = \
  [ \
    0, \
    1, \
    0.5773502692, \
    0.4030076571, \
    0.3086066999, \
    0.2496411504, \
    0.2093977333, \
    0.1802208568, \
    0.1581178777, \
  ]

# Bessel -3dB cut-off frequency normalization factors (filter order: 0, 1, 2, 3, etc.)
bessel_normalization_minus_3dB = \
  [ \
    0, \
    1, \
    0.7344008871, \
    0.5695823537, \
    0.4730553190, \
    0.4119616014, \
    0.3699052404, \
    0.3387852752, \
    0.3145032642, \
  ]

# Bessel -6dB cut-off frequency normalization factors (filter order: 0, 1, 2, 3, etc.)
bessel_normalization_minus_6dB = \
  [ \
    0, \
    0.5773502692, \
    0.5058299712, \
    0.4124480612, \
    0.3464976033, \
    0.3008282922, \
    0.2683441713, \
    0.2443748483, \
    0.2259597827, \
  ]

# Linkwitz-Riley damping factors (filter order: 0, 2, 4, 6, etc.)
#     1st section   2nd section   3rd section   4th section
#     -----------------------------------------------------
linkwitz_riley_damping = \
  [ \
    [ 0,            0,            0,            0,           ], \
    [ 2.0,          0,            0,            0,           ], \
    [ 1.4142135624, 1.4142135624, 0,            0,           ], \
    [ 2.0,          1.0,          1.0,          0,           ], \
    [ 1.8477590650, 0.7653668647, 1.8477590650, 0.7653668647 ] \
  ]

# enum bessel_norm_e
phase_match = 0
time_delay = 1
minus_3dB = 2
minus_6dB = 3
unnormalized = 4

# enum filter_type_e
variable_q = 0
butterworth = 1
linkwitz_riley = 2
bessel = 3

two_pi = 2 * math.pi
omega_min = two_pi * ( .01 / 192000 )
omega_max = two_pi * ( 22000. / 48000 )

#message.string_set( "type = " + str( type ) )

# variable-Q filter must be second order
if type == variable_q :
  order = 2
# Linkwitz-Riley filter must be even order
else :
  if type == linkwitz_riley and math.fmod( order, 2 ) != 0 :
    order = order + 1

# limit order
if order < 1 : order = 1
if order > max_order : order = max_order

# compute normalized cut-off frequency in rad/s
omega_c = two_pi * frequency / sample_rate
if omega_c < omega_min : omega_c = omega_min
if omega_c > omega_max : omega_c = omega_max

# working filter order
working_order = order;

if bypass :
  working_order = 0

# compute gain (first biquad implements gain)
k = math.pow( 10, gain / 20 )

if invert :
  k = -k

if mute :
  k = 0

#message.string_set( "--------------" )
#message.string_set( "k = " + str( k ) )

# for each biquad do...
for biquad in range( max_biquad ) :

#  message.string_set( "working_order = " + str( working_order ) )

  # nominal normalized cut-off frequency
  omega = omega_c;

  # Bessel filter frequency scaling
  if type == bessel :
    if normalization == phase_match :
      if low_pass :
        omega = omega * bessel_normalization_phase_match[ order ]
      else : # high
        omega = omega / bessel_normalization_phase_match[ order ]
    else :
      if normalization == time_delay : # low-pass only!
        omega = omega / two_pi # from rad/s back to 1/s
      else :
        if normalization == minus_3dB :
          if low_pass :
            omega = omega * bessel_normalization_minus_3dB[ order ]
          else : # high
            omega = omega / bessel_normalization_minus_3dB[ order ]
        else :
          if normalization == minus_6dB :
            if low_pass :
              omega = omega * bessel_normalization_minus_6dB[ order ]
            else : # high
              omega = omega / bessel_normalization_minus_6dB[ order ]

  # compute filter coefficients
  if working_order == 0 : # either one-and-only or last first-order section

#    message.string_set( "zeroth-order section" )

    a = 0 # not used
    b = math.cos( omega ) # not used but seems to reduce order change artifacts...
    c = -1 # transparent section
  else :
    if working_order == 1 : # either one-and-only or last first-order section
  
#      message.string_set( "first-order section" )
  
      if type == bessel :
        if low_pass :
          omega = omega * bessel_frequency_first_order[ biquad ]
        else : # high
          omega = omega / bessel_frequency_first_order[ biquad ]
        if omega < omega_min : omega = omega_min
        if omega > omega_max : omega = omega_max
      a = ( math.cos( omega ) + math.sin( omega ) - 1 ) / \
          ( math.cos( omega ) - math.sin( omega ) - 1 )
      b = math.cos( omega ) # not used but seems to reduce order change artifacts...
      c = 0 # first-order section
      working_order = working_order - 1
    else : # second order section

#      message.string_set( "second-order section" )

      if type == variable_q : # second-order only!
        damping = 1 / q_factor
      else :
        if type == bessel :
          damping = bessel_damping[ order ][ biquad ]
          if low_pass :
            omega = omega * bessel_frequency[ order ][ biquad ]
          else : # high
            omega = omega / bessel_frequency[ order ][ biquad ]
          if omega < omega_min : omega = omega_min
          if omega > omega_max : omega = omega_max
        else :
          if ( type == butterworth ) or ( type == linkwitz_riley ) :
            if type == linkwitz_riley :
              damping = linkwitz_riley_damping[ order / 2 ][ biquad ]
            else : # Butterworth
              damping = 2 * math.sin( math.pi * ( 1 + 2 * ( order / 2 - 1 - biquad ) ) / ( 2 * order ) );
          else :
            # should never get here!
            damping = 0
            message.string_set( "low pass filter internal error!" )

#      message.string_set( "biquad = %d, damping = %5.20f" % ( biquad, damping ) )

      a = ( 2 - damping * math.sin( omega ) ) / \
          ( 2 + damping * math.sin( omega ) )
      # negate parameter 'a' for second quadrant of unit circle to reduce sweep noise
      if omega > ( math.pi / 2 ) : a = -a
      b = math.cos( omega )
      c = 1 # second-order section
      working_order = working_order - 2

  exec "a_%d = a" % ( biquad+1 )
  exec "b_%d = b" % ( biquad+1 )
  exec "c_%d = c" % ( biquad+1 )

#  message.string_set( "a_%d = %5.20f" % ( biquad+1, a ) )
#  message.string_set( "b_%d = %5.20f" % ( biquad+1, b ) )
#  message.string_set( "c_%d = %5.20f" % ( biquad+1, c ) )

	  
poke_list = [[hold_count,0,1],[ramp,31,1],[k,30,1],[a_1,31,1],[b_1,31,1],[c_1,0,1]]
dsp.poke_multiple( 0x1, 70, poke_list )

#peek_crunch_function_filter_highpass_transposed_direct_II_64==================================================================================13
clip = dsp.peek(0x0,18,0,1)
property = {  'max_order':'2','low_pass':'0','scale_factor':'1','available_mips':'115','block_size':'16','chip_required':'49600','clip_hold_time':'1','compile_debug':'0','external_mem_address':'0','external_mem_enabled':'false','external_mem_size':'0','firmware_version':'<current>','overlay':'cc','pacman_poll_rate':'10','ramp_time_constant':'0.075','sample_rate':'48000','target_dsp':'all','x_heap_size':'0','x_memory_size':'2000','y_heap_size':'0','y_memory_size':'8000' }

# python function for crunching read-only output control values

#message.string_set( "clip = " + str( clip ) )
#message.string_set( "b0_0 = " + str( b0_0 ) )
#message.string_set( "b1_0 = " + str( b1_0 ) )
#message.string_set( "a1_0 = " + str( a1_0 ) )
#message.string_set( "a2_0 = " + str( a2_0 ) )
#message.string_set( "b0_1 = " + str( b0_1 ) )
#message.string_set( "b1_1 = " + str( b1_1 ) )
#message.string_set( "a1_1 = " + str( a1_1 ) )
#message.string_set( "a2_1 = " + str( a2_1 ) )

	  
outputs[0].value_set(clip)

#peek_crunch_function_equalizer_parametric_transposed_direct_II_175==================================================================================14
clip = dsp.peek(0x0,35,0,1)
property = {  'scale_factor':'1',
'available_mips':'115',
'block_size':'16',
'chip_required':'49600',
'clip_hold_time':'1',
'compile_debug':'0',
'external_mem_address':'0',
'external_mem_enabled':'false',
'external_mem_size':'0',
'firmware_version':'<current>',
'overlay':'cc','pacman_poll_rate':'10',
'ramp_time_constant':'0.075',
'sample_rate':'48000',
'target_dsp':'all',
'x_heap_size':'0',
'x_memory_size':'2000',
'y_heap_size':'0',
'y_memory_size':'8000' }
# python function for crunching read-only output control values
#message.string_set( "clip = " + str( clip ) )
outputs[0].value_set(clip)

#poke_crunch_function_equalizer_parametric_transposed_direct_II_175==================================================================================15
bandwidth = inputs[0].value_get()
frequency = inputs[1].value_get()
gain = inputs[2].value_get()
property = {  'scale_factor':'1',
'available_mips':'115',
'block_size':'16',
'chip_required':'49600',
'clip_hold_time':'1',
'compile_debug':'0',
'external_mem_address':'0',
'external_mem_enabled':'false',
'external_mem_size':'0',
'firmware_version':'<current>',
'overlay':'cc',
'pacman_poll_rate':'10',
'ramp_time_constant':'0.075',
'sample_rate':'48000',
'target_dsp':'all',
'x_heap_size':'0',
'x_memory_size':'2000',
'y_heap_size':'0',
'y_memory_size':'8000' }
# python function for crunching input control values
scale_factor = float( property[ "scale_factor" ] )
sample_rate = float( property[ "sample_rate" ] ) * scale_factor
block_size = float( property[ "block_size" ] ) * scale_factor
ramp_time_constant = float( property[ "ramp_time_constant" ] )
clip_hold_time = float( property[ "clip_hold_time" ] )

block_rate = sample_rate / block_size
ramp = 1 - math.exp( -1 / ( ramp_time_constant * block_rate ) )
hold_count = clip_hold_time * block_rate

two_pi = 6.283185307179586476925286766559
omega_c = two_pi * frequency / sample_rate
sin_omega_c = math.sin( omega_c )
cos_omega_c = math.cos( omega_c )
g = math.pow( 10, gain / 20 )
q = math.pow( 2, bandwidth / 2 )
q = q / ( q * q - 1 )

# pre-warp Q-factor (compensate for bilinear transform)
omega_3 = omega_c * ( math.sqrt( 4 * q * q + 1 ) - 1 ) / ( q + q )
q = ( math.sin( omega_3 ) * sin_omega_c ) / ( 2 * ( math.cos( omega_3 ) - cos_omega_c ) )

# adjust Q-factor if cut (symmetric response)
if( gain < 0 ) :
  q = q * g

# compute intermediate coefficients
a = ( 2 * q - sin_omega_c ) / ( 2 * q + sin_omega_c )
b = cos_omega_c
minus_one = -1

#message.string_set( "ramp = " + str( ramp ) )
#message.string_set( "hold_count = " + str( hold_count ) )
#message.string_set( "a = " + str( a ) )
#message.string_set( "b = " + str( b ) )
#message.string_set( "g = " + str( g ) )
  
poke_list = [[ramp,31,1],[a,31,1],[b,31,1],[g,29,1],[minus_one,31,1],[hold_count,0,1]]
dsp.poke_multiple( 0x1, 160, poke_list )


#peek_crunch_function_mixer_NxM_6==================================================================================16

output_clip_1 = dsp.peek(0x0,216,0,1)
output_clip_2 = dsp.peek(0x0,217,0,1)
output_clip_3 = dsp.peek(0x0,218,0,1)
output_clip_4 = dsp.peek(0x0,219,0,1)
output_clip_5 = dsp.peek(0x0,220,0,1)
output_clip_6 = dsp.peek(0x0,221,0,1)
property = {  'input_count':'18','output_count':'6','scale_factor':'1','available_mips':'115','block_size':'16','chip_required':'49600','clip_hold_time':'1','compile_debug':'0','external_mem_address':'0','external_mem_enabled':'false','external_mem_size':'0','firmware_version':'<current>','overlay':'cc','pacman_poll_rate':'10','ramp_time_constant':'0.075','sample_rate':'48000','target_dsp':'all','x_heap_size':'0','x_memory_size':'2000','y_heap_size':'0','y_memory_size':'8000' }

# python function for crunching read-only control values
output_count = int( property[ "output_count"] )
for i in range(output_count):
  exec "output_clip_%d = not not output_clip_%d" % ( i+1, i+1 )

    
outputs[0].value_set(output_clip_1)
outputs[1].value_set(output_clip_2)
outputs[2].value_set(output_clip_3)
outputs[3].value_set(output_clip_4)
outputs[4].value_set(output_clip_5)
outputs[5].value_set(output_clip_6)

#poke_crunch_function_gain_up_24dB_multi_channel_218==================================================================================17
channel_gain_1 = inputs[0].value_get()
channel_gain_10 = inputs[1].value_get()
channel_gain_11 = inputs[2].value_get()
channel_gain_12 = inputs[3].value_get()
channel_gain_13 = inputs[4].value_get()
channel_gain_14 = inputs[5].value_get()
channel_gain_15 = inputs[6].value_get()
channel_gain_16 = inputs[7].value_get()
channel_gain_2 = inputs[8].value_get()
channel_gain_3 = inputs[9].value_get()
channel_gain_4 = inputs[10].value_get()
channel_gain_5 = inputs[11].value_get()
channel_gain_6 = inputs[12].value_get()
channel_gain_7 = inputs[13].value_get()
channel_gain_8 = inputs[14].value_get()
channel_gain_9 = inputs[15].value_get()
channel_invert_1 = inputs[16].value_get()
channel_invert_10 = inputs[17].value_get()
channel_invert_11 = inputs[18].value_get()
channel_invert_12 = inputs[19].value_get()
channel_invert_13 = inputs[20].value_get()
channel_invert_14 = inputs[21].value_get()
channel_invert_15 = inputs[22].value_get()
channel_invert_16 = inputs[23].value_get()
channel_invert_2 = inputs[24].value_get()
channel_invert_3 = inputs[25].value_get()
channel_invert_4 = inputs[26].value_get()
channel_invert_5 = inputs[27].value_get()
channel_invert_6 = inputs[28].value_get()
channel_invert_7 = inputs[29].value_get()
channel_invert_8 = inputs[30].value_get()
channel_invert_9 = inputs[31].value_get()
channel_mute_1 = inputs[32].value_get()
channel_mute_10 = inputs[33].value_get()
channel_mute_11 = inputs[34].value_get()
channel_mute_12 = inputs[35].value_get()
channel_mute_13 = inputs[36].value_get()
channel_mute_14 = inputs[37].value_get()
channel_mute_15 = inputs[38].value_get()
channel_mute_16 = inputs[39].value_get()
channel_mute_2 = inputs[40].value_get()
channel_mute_3 = inputs[41].value_get()
channel_mute_4 = inputs[42].value_get()
channel_mute_5 = inputs[43].value_get()
channel_mute_6 = inputs[44].value_get()
channel_mute_7 = inputs[45].value_get()
channel_mute_8 = inputs[46].value_get()
channel_mute_9 = inputs[47].value_get()
property = {  'channel_count':'16','scale_factor':'1','available_mips':'115','block_size':'16','chip_required':'49600','clip_hold_time':'1','compile_debug':'0','external_mem_address':'0','external_mem_enabled':'false','external_mem_size':'0','firmware_version':'<current>','overlay':'cc','pacman_poll_rate':'10','ramp_time_constant':'0.075','sample_rate':'48000','target_dsp':'all','x_heap_size':'0','x_memory_size':'2000','y_heap_size':'0','y_memory_size':'8000' }

# python function for crunching input control values

scale_factor = float( property[ "scale_factor" ] )
sample_rate = float( property[ "sample_rate" ] ) * scale_factor
block_size = float( property[ "block_size" ] ) * scale_factor
ramp_time_constant = float( property[ "ramp_time_constant" ] )
clip_hold_time = float( property[ "clip_hold_time" ] )
channel_count = int( property[ "channel_count"] )

block_rate = sample_rate / block_size
ramp = 1 - math.exp( -1 / ( ramp_time_constant * block_rate ) )
hold_count = clip_hold_time * block_rate

#message.string_set( "ramp = " + str( ramp ) )
#message.string_set( "hold_count = " + str( hold_count ) )

channel_mute = [0] * channel_count
channel_invert = [1] * channel_count
channel_gain = [0] * channel_count

for i in range( channel_count ) :
  channel_mute[ i ] = not eval( "channel_mute_" + str( i + 1 ) )
  if( eval( "channel_invert_" + str( i + 1) ) ) : channel_invert[ i ] = -1
  channel_gain[ i ] = -math.pow( 10, eval( "channel_gain_" + str( i + 1 ) ) / 20 )
  if eval( "channel_gain_" + str( i + 1 ) ) <= -100 : channel_gain[ i ] = 0

# gain[i]  = channel_mute[i] * channel_invert[i] * channel_gain[i]

for i in range( channel_count ) :
  g = channel_mute[ i ] * channel_invert[ i ] * channel_gain[ i ]
  exec "g_%d = %f" % ( i + 1, g )
#  message.string_set( "g_%d = %f" % ( i + 1, g ) )

	  
poke_list = [[hold_count,0,1],[ramp,31,1],[g_1,31,1],[g_2,31,1],[g_3,31,1],[g_4,31,1],[g_5,31,1],[g_6,31,1],[g_7,31,1],[g_8,31,1],[g_9,31,1],[g_10,31,1],[g_11,31,1],[g_12,31,1],[g_13,31,1],[g_14,31,1],[g_15,31,1],[g_16,31,1]]
dsp.poke_multiple( 0x1, 814, poke_list )

#peek_crunch_function_gain_up_24dB_multi_channel_218==================================================================================18
channel_clip_1 = dsp.peek(0x0,226,0,1)
channel_clip_10 = dsp.peek(0x0,235,0,1)
channel_clip_11 = dsp.peek(0x0,236,0,1)
channel_clip_12 = dsp.peek(0x0,237,0,1)
channel_clip_13 = dsp.peek(0x0,238,0,1)
channel_clip_14 = dsp.peek(0x0,239,0,1)
channel_clip_15 = dsp.peek(0x0,240,0,1)
channel_clip_16 = dsp.peek(0x0,241,0,1)
channel_clip_2 = dsp.peek(0x0,227,0,1)
channel_clip_3 = dsp.peek(0x0,228,0,1)
channel_clip_4 = dsp.peek(0x0,229,0,1)
channel_clip_5 = dsp.peek(0x0,230,0,1)
channel_clip_6 = dsp.peek(0x0,231,0,1)
channel_clip_7 = dsp.peek(0x0,232,0,1)
channel_clip_8 = dsp.peek(0x0,233,0,1)
channel_clip_9 = dsp.peek(0x0,234,0,1)
property = {  'channel_count':'16','scale_factor':'1','available_mips':'115','block_size':'16','chip_required':'49600','clip_hold_time':'1','compile_debug':'0','external_mem_address':'0','external_mem_enabled':'false','external_mem_size':'0','firmware_version':'<current>','overlay':'cc','pacman_poll_rate':'10','ramp_time_constant':'0.075','sample_rate':'48000','target_dsp':'all','x_heap_size':'0','x_memory_size':'2000','y_heap_size':'0','y_memory_size':'8000' }

# python function for crunching read-only output control values

channel_count = int( property[ "channel_count"] )

clip = 0
for i in range( channel_count ) :
#  exec "channel_clip_%d = not not channel_clip_%d" % ( i + 1, i + 1 )
  channel_clip = eval( "channel_clip_" + str( i + 1 ) )
#  message.string_set( "clip_%d = %f" % ( i + 1, channel_clip ) )
  clip = clip or channel_clip

#message.string_set( "clip = " + str( clip ) )

	  
outputs[0].value_set(channel_clip_1)
outputs[1].value_set(channel_clip_10)
outputs[2].value_set(channel_clip_11)
outputs[3].value_set(channel_clip_12)
outputs[4].value_set(channel_clip_13)
outputs[5].value_set(channel_clip_14)
outputs[6].value_set(channel_clip_15)
outputs[7].value_set(channel_clip_16)
outputs[8].value_set(channel_clip_2)
outputs[9].value_set(channel_clip_3)
outputs[10].value_set(channel_clip_4)
outputs[11].value_set(channel_clip_5)
outputs[12].value_set(channel_clip_6)
outputs[13].value_set(channel_clip_7)
outputs[14].value_set(channel_clip_8)
outputs[15].value_set(channel_clip_9)

