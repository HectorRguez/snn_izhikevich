; ModuleID = 'C:/automate_snn_hls/snn_izhikevich/proj/solution/.autopilot/db/a.g.ld.5.gdce.bc'
source_filename = "llvm-link"
target datalayout = "e-m:e-i64:64-i128:128-i256:256-i512:512-i1024:1024-i2048:2048-i4096:4096-n8:16:32:64-S128-v16:16-v24:32-v32:32-v48:64-v96:128-v192:256-v256:256-v512:512-v1024:1024"
target triple = "fpga64-xilinx-none"

%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>" = type { %"struct.hls::axis<ap_int<64>, 0, 0, 0>" }
%"struct.hls::axis<ap_int<64>, 0, 0, 0>" = type { %"struct.ap_uint<64>", %"struct.ap_uint<8>", %"struct.ap_uint<8>", %"struct.ap_uint<1>", %"struct.ap_uint<1>", %"struct.ap_uint<1>", %"struct.ap_uint<1>" }
%"struct.ap_uint<64>" = type { %"struct.ap_int_base<64, false>" }
%"struct.ap_int_base<64, false>" = type { %"struct.ssdm_int<64, false>" }
%"struct.ssdm_int<64, false>" = type { i64 }
%"struct.ap_uint<8>" = type { %"struct.ap_int_base<8, false>" }
%"struct.ap_int_base<8, false>" = type { %"struct.ssdm_int<8, false>" }
%"struct.ssdm_int<8, false>" = type { i8 }
%"struct.ap_uint<1>" = type { %"struct.ap_int_base<1, false>" }
%"struct.ap_int_base<1, false>" = type { %"struct.ssdm_int<1, false>" }
%"struct.ssdm_int<1, false>" = type { i1 }

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_in([1 x i32]* noalias readonly, [1 x i32]* noalias align 512, [2 x i32]* noalias readonly, [2 x i32]* noalias align 512, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias, i64* noalias "unpacked"="5.0" %_V_data_V, i8* noalias "unpacked"="5.1" %_V_keep_V, i8* noalias "unpacked"="5.2" %_V_strb_V, i1* noalias "unpacked"="5.3" %_V_last_V, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias, i64* noalias "unpacked"="7.0" %_V_data_V1, i8* noalias "unpacked"="7.1" %_V_keep_V2, i8* noalias "unpacked"="7.2" %_V_strb_V3, i1* noalias "unpacked"="7.3" %_V_last_V4, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias, i64* noalias "unpacked"="9.0" %_V_data_V15, i8* noalias "unpacked"="9.1" %_V_keep_V26, i8* noalias "unpacked"="9.2" %_V_strb_V37, i1* noalias "unpacked"="9.3" %_V_last_V48, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias, i64* noalias "unpacked"="11.0" %_V_data_V159, i8* noalias "unpacked"="11.1" %_V_keep_V2610, i8* noalias "unpacked"="11.2" %_V_strb_V3711, i1* noalias "unpacked"="11.3" %_V_last_V4812, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias, i64* noalias "unpacked"="25.0" %_V_data_V2, i8* noalias "unpacked"="25.1" %_V_keep_V3, i8* noalias "unpacked"="25.2" %_V_strb_V4, i1* noalias "unpacked"="25.3" %_V_last_V5) unnamed_addr #0 {
entry:
  call fastcc void @onebyonecpy_hls.p0a1i32([1 x i32]* align 512 %1, [1 x i32]* %0)
  call fastcc void @onebyonecpy_hls.p0a2i32([2 x i32]* align 512 %3, [2 x i32]* %2)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"(i64* %_V_data_V, i8* %_V_keep_V, i8* %_V_strb_V, i1* %_V_last_V, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %4)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"(i64* %_V_data_V1, i8* %_V_keep_V2, i8* %_V_strb_V3, i1* %_V_last_V4, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %5)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"(i64* %_V_data_V15, i8* %_V_keep_V26, i8* %_V_strb_V37, i1* %_V_last_V48, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %6)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"(i64* %_V_data_V159, i8* %_V_keep_V2610, i8* %_V_strb_V3711, i1* %_V_last_V4812, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %7)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"(i64* %_V_data_V2, i8* %_V_keep_V3, i8* %_V_strb_V4, i1* %_V_last_V5, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %8)
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a1i32([1 x i32]* noalias align 512 %dst, [1 x i32]* noalias readonly %src) unnamed_addr #1 {
entry:
  %0 = icmp eq [1 x i32]* %dst, null
  %1 = icmp eq [1 x i32]* %src, null
  %2 = or i1 %0, %1
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  call void @arraycpy_hls.p0a1i32([1 x i32]* nonnull %dst, [1 x i32]* nonnull %src, i64 1)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define void @arraycpy_hls.p0a1i32([1 x i32]* %dst, [1 x i32]* readonly %src, i64 %num) local_unnamed_addr #2 {
entry:
  %0 = icmp eq [1 x i32]* %src, null
  %1 = icmp eq [1 x i32]* %dst, null
  %2 = or i1 %1, %0
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %for.loop.cond1 = icmp sgt i64 %num, 0
  br i1 %for.loop.cond1, label %for.loop.lr.ph, label %copy.split

for.loop.lr.ph:                                   ; preds = %copy
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %for.loop.lr.ph
  %for.loop.idx2 = phi i64 [ 0, %for.loop.lr.ph ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [1 x i32], [1 x i32]* %dst, i64 0, i64 %for.loop.idx2
  %src.addr = getelementptr [1 x i32], [1 x i32]* %src, i64 0, i64 %for.loop.idx2
  %3 = load i32, i32* %src.addr, align 4
  store i32 %3, i32* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx2, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, %num
  br i1 %exitcond, label %for.loop, label %copy.split

copy.split:                                       ; preds = %for.loop, %copy
  br label %ret

ret:                                              ; preds = %copy.split, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define internal fastcc void @onebyonecpy_hls.p0a2i32([2 x i32]* noalias align 512 %dst, [2 x i32]* noalias readonly %src) unnamed_addr #1 {
entry:
  %0 = icmp eq [2 x i32]* %dst, null
  %1 = icmp eq [2 x i32]* %src, null
  %2 = or i1 %0, %1
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  call void @arraycpy_hls.p0a2i32([2 x i32]* nonnull %dst, [2 x i32]* nonnull %src, i64 2)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline norecurse
define void @arraycpy_hls.p0a2i32([2 x i32]* %dst, [2 x i32]* readonly %src, i64 %num) local_unnamed_addr #2 {
entry:
  %0 = icmp eq [2 x i32]* %src, null
  %1 = icmp eq [2 x i32]* %dst, null
  %2 = or i1 %1, %0
  br i1 %2, label %ret, label %copy

copy:                                             ; preds = %entry
  %for.loop.cond1 = icmp sgt i64 %num, 0
  br i1 %for.loop.cond1, label %for.loop.lr.ph, label %copy.split

for.loop.lr.ph:                                   ; preds = %copy
  br label %for.loop

for.loop:                                         ; preds = %for.loop, %for.loop.lr.ph
  %for.loop.idx2 = phi i64 [ 0, %for.loop.lr.ph ], [ %for.loop.idx.next, %for.loop ]
  %dst.addr = getelementptr [2 x i32], [2 x i32]* %dst, i64 0, i64 %for.loop.idx2
  %src.addr = getelementptr [2 x i32], [2 x i32]* %src, i64 0, i64 %for.loop.idx2
  %3 = load i32, i32* %src.addr, align 4
  store i32 %3, i32* %dst.addr, align 4
  %for.loop.idx.next = add nuw nsw i64 %for.loop.idx2, 1
  %exitcond = icmp ne i64 %for.loop.idx.next, %num
  br i1 %exitcond, label %for.loop, label %copy.split

copy.split:                                       ; preds = %for.loop, %copy
  br label %ret

ret:                                              ; preds = %copy.split, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_out([1 x i32]* noalias, [1 x i32]* noalias readonly align 512, [2 x i32]* noalias, [2 x i32]* noalias readonly align 512, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias, i64* noalias "unpacked"="5.0" %_V_data_V, i8* noalias "unpacked"="5.1" %_V_keep_V, i8* noalias "unpacked"="5.2" %_V_strb_V, i1* noalias "unpacked"="5.3" %_V_last_V, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias, i64* noalias "unpacked"="7.0" %_V_data_V1, i8* noalias "unpacked"="7.1" %_V_keep_V2, i8* noalias "unpacked"="7.2" %_V_strb_V3, i1* noalias "unpacked"="7.3" %_V_last_V4, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias, i64* noalias "unpacked"="9.0" %_V_data_V15, i8* noalias "unpacked"="9.1" %_V_keep_V26, i8* noalias "unpacked"="9.2" %_V_strb_V37, i1* noalias "unpacked"="9.3" %_V_last_V48, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias, i64* noalias "unpacked"="11.0" %_V_data_V159, i8* noalias "unpacked"="11.1" %_V_keep_V2610, i8* noalias "unpacked"="11.2" %_V_strb_V3711, i1* noalias "unpacked"="11.3" %_V_last_V4812, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias, i64* noalias "unpacked"="25.0" %_V_data_V2, i8* noalias "unpacked"="25.1" %_V_keep_V3, i8* noalias "unpacked"="25.2" %_V_strb_V4, i1* noalias "unpacked"="25.3" %_V_last_V5) unnamed_addr #3 {
entry:
  call fastcc void @onebyonecpy_hls.p0a1i32([1 x i32]* %0, [1 x i32]* align 512 %1)
  call fastcc void @onebyonecpy_hls.p0a2i32([2 x i32]* %2, [2 x i32]* align 512 %3)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>.20"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %4, i64* %_V_data_V, i8* %_V_keep_V, i8* %_V_strb_V, i1* %_V_last_V)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>.20"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %5, i64* %_V_data_V1, i8* %_V_keep_V2, i8* %_V_strb_V3, i1* %_V_last_V4)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>.20"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %6, i64* %_V_data_V15, i8* %_V_keep_V26, i8* %_V_strb_V37, i1* %_V_last_V48)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>.20"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %7, i64* %_V_data_V159, i8* %_V_keep_V2610, i8* %_V_strb_V3711, i1* %_V_last_V4812)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>.20"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %8, i64* %_V_data_V2, i8* %_V_keep_V3, i8* %_V_strb_V4, i1* %_V_last_V5)
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>.20"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias align 512 %dst, i64* noalias "unpacked"="1.0" %src_V_data_V, i8* noalias "unpacked"="1.1" %src_V_keep_V, i8* noalias "unpacked"="1.2" %src_V_strb_V, i1* noalias "unpacked"="1.3" %src_V_last_V) unnamed_addr #4 {
entry:
  %0 = icmp eq %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %dst, null
  %1 = or i1 %0, false
  br i1 %1, label %ret, label %copy

copy:                                             ; preds = %entry
  call fastcc void @"streamcpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>.23"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* nonnull align 512 %dst, i64* %src_V_data_V, i8* %src_V_keep_V, i8* %src_V_strb_V, i1* %src_V_last_V)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>.23"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias nocapture align 512, i64* noalias nocapture "unpacked"="1.0" %_V_data_V, i8* noalias nocapture "unpacked"="1.1" %_V_keep_V, i8* noalias nocapture "unpacked"="1.2" %_V_strb_V, i1* noalias nocapture "unpacked"="1.3" %_V_last_V) unnamed_addr #5 {
entry:
  %1 = alloca %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"
  %2 = alloca i64
  %3 = alloca i8
  %4 = alloca i8
  %5 = alloca i1
  br label %empty

empty:                                            ; preds = %push, %entry
  %6 = bitcast i64* %_V_data_V to i8*
  %7 = call i1 @fpga_fifo_not_empty_8(i8* %6)
  br i1 %7, label %push, label %ret

push:                                             ; preds = %empty
  %8 = bitcast i64* %2 to i8*
  %9 = bitcast i64* %_V_data_V to i8*
  call void @fpga_fifo_pop_8(i8* %8, i8* %9)
  %10 = load volatile i64, i64* %2
  %11 = getelementptr inbounds %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>", %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %1, i32 0, i32 0, i32 0
  %12 = bitcast %"struct.ap_uint<64>"* %11 to i64*
  store i64 %10, i64* %12
  call void @fpga_fifo_pop_1(i8* %4, i8* %_V_keep_V)
  %13 = load volatile i8, i8* %4
  %14 = getelementptr inbounds %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>", %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %1, i32 0, i32 0, i32 1
  %15 = bitcast %"struct.ap_uint<8>"* %14 to i8*
  store i8 %13, i8* %15
  call void @fpga_fifo_pop_1(i8* %3, i8* %_V_strb_V)
  %16 = load volatile i8, i8* %3
  %17 = getelementptr inbounds %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>", %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %1, i32 0, i32 0, i32 2
  %18 = bitcast %"struct.ap_uint<8>"* %17 to i8*
  store i8 %16, i8* %18
  %19 = bitcast i1* %5 to i8*
  %20 = bitcast i1* %_V_last_V to i8*
  call void @fpga_fifo_pop_1(i8* %19, i8* %20)
  %21 = bitcast i1* %5 to i8*
  %22 = load i8, i8* %21
  %23 = trunc i8 %22 to i1
  %24 = getelementptr inbounds %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>", %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %1, i32 0, i32 0, i32 4
  %25 = bitcast %"struct.ap_uint<1>"* %24 to i1*
  store i1 %23, i1* %25
  %26 = bitcast %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %1 to i8*
  %27 = bitcast %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %0 to i8*
  call void @fpga_fifo_push_16(i8* %26, i8* %27)
  br label %empty, !llvm.loop !5

ret:                                              ; preds = %empty
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"(i64* noalias "unpacked"="0.0" %dst_V_data_V, i8* noalias "unpacked"="0.1" %dst_V_keep_V, i8* noalias "unpacked"="0.2" %dst_V_strb_V, i1* noalias "unpacked"="0.3" %dst_V_last_V, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias %src) unnamed_addr #4 {
entry:
  %0 = icmp eq %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %src, null
  %1 = or i1 false, %0
  br i1 %1, label %ret, label %copy

copy:                                             ; preds = %entry
  call fastcc void @"streamcpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>.30"(i64* %dst_V_data_V, i8* %dst_V_keep_V, i8* %dst_V_strb_V, i1* %dst_V_last_V, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* nonnull %src)
  br label %ret

ret:                                              ; preds = %copy, %entry
  ret void
}

; Function Attrs: argmemonly noinline
define internal fastcc void @"streamcpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>.30"(i64* noalias nocapture "unpacked"="0.0" %_V_data_V, i8* noalias nocapture "unpacked"="0.1" %_V_keep_V, i8* noalias nocapture "unpacked"="0.2" %_V_strb_V, i1* noalias nocapture "unpacked"="0.3" %_V_last_V, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias nocapture) unnamed_addr #5 {
entry:
  %1 = alloca %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"
  %2 = alloca %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"
  br label %empty

empty:                                            ; preds = %push, %entry
  %3 = bitcast %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %0 to i8*
  %4 = call i1 @fpga_fifo_not_empty_16(i8* %3)
  br i1 %4, label %push, label %ret

push:                                             ; preds = %empty
  %5 = bitcast %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %2 to i8*
  %6 = bitcast %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %0 to i8*
  call void @fpga_fifo_pop_16(i8* %5, i8* %6)
  %7 = load volatile %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>", %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %2
  store %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>" %7, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %1
  %8 = getelementptr inbounds %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>", %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %1, i32 0, i32 0, i32 0
  %9 = bitcast %"struct.ap_uint<64>"* %8 to i64*
  %10 = bitcast i64* %9 to i8*
  %11 = bitcast i64* %_V_data_V to i8*
  call void @fpga_fifo_push_8(i8* %10, i8* %11)
  %12 = getelementptr inbounds %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>", %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %1, i32 0, i32 0, i32 1
  %13 = bitcast %"struct.ap_uint<8>"* %12 to i8*
  call void @fpga_fifo_push_1(i8* %13, i8* %_V_keep_V)
  %14 = getelementptr inbounds %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>", %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %1, i32 0, i32 0, i32 2
  %15 = bitcast %"struct.ap_uint<8>"* %14 to i8*
  call void @fpga_fifo_push_1(i8* %15, i8* %_V_strb_V)
  %16 = getelementptr inbounds %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>", %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %1, i32 0, i32 0, i32 4
  %17 = bitcast %"struct.ap_uint<1>"* %16 to i1*
  %18 = bitcast i1* %17 to i8*
  %19 = bitcast i1* %_V_last_V to i8*
  call void @fpga_fifo_push_1(i8* %18, i8* %19)
  br label %empty, !llvm.loop !5

ret:                                              ; preds = %empty
  ret void
}

declare void @apatb_hls_snn_izikevich_hw(%"struct.ap_uint<1>"*, %"struct.ap_uint<1>"*, [1 x i32]*, [2 x i32]*, i64*, i8*, i8*, i1*, i64*, i8*, i8*, i1*, i64*, i8*, i8*, i1*, i64*, i8*, i8*, i1*, i64*, i8*, i8*, i1*)

; Function Attrs: argmemonly noinline
define internal fastcc void @copy_back([1 x i32]* noalias, [1 x i32]* noalias readonly align 512, [2 x i32]* noalias, [2 x i32]* noalias readonly align 512, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias, i64* noalias "unpacked"="5.0" %_V_data_V, i8* noalias "unpacked"="5.1" %_V_keep_V, i8* noalias "unpacked"="5.2" %_V_strb_V, i1* noalias "unpacked"="5.3" %_V_last_V, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias, i64* noalias "unpacked"="7.0" %_V_data_V1, i8* noalias "unpacked"="7.1" %_V_keep_V2, i8* noalias "unpacked"="7.2" %_V_strb_V3, i1* noalias "unpacked"="7.3" %_V_last_V4, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias, i64* noalias "unpacked"="9.0" %_V_data_V15, i8* noalias "unpacked"="9.1" %_V_keep_V26, i8* noalias "unpacked"="9.2" %_V_strb_V37, i1* noalias "unpacked"="9.3" %_V_last_V48, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias, i64* noalias "unpacked"="11.0" %_V_data_V159, i8* noalias "unpacked"="11.1" %_V_keep_V2610, i8* noalias "unpacked"="11.2" %_V_strb_V3711, i1* noalias "unpacked"="11.3" %_V_last_V4812, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias, i64* noalias "unpacked"="25.0" %_V_data_V2, i8* noalias "unpacked"="25.1" %_V_keep_V3, i8* noalias "unpacked"="25.2" %_V_strb_V4, i1* noalias "unpacked"="25.3" %_V_last_V5) unnamed_addr #3 {
entry:
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>.20"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %4, i64* %_V_data_V, i8* %_V_keep_V, i8* %_V_strb_V, i1* %_V_last_V)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>.20"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %5, i64* %_V_data_V1, i8* %_V_keep_V2, i8* %_V_strb_V3, i1* %_V_last_V4)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>.20"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %6, i64* %_V_data_V15, i8* %_V_keep_V26, i8* %_V_strb_V37, i1* %_V_last_V48)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>.20"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %7, i64* %_V_data_V159, i8* %_V_keep_V2610, i8* %_V_strb_V3711, i1* %_V_last_V4812)
  call fastcc void @"onebyonecpy_hls.p0class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>.20"(%"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %8, i64* %_V_data_V2, i8* %_V_keep_V3, i8* %_V_strb_V4, i1* %_V_last_V5)
  ret void
}

define void @hls_snn_izikevich_hw_stub_wrapper(%"struct.ap_uint<1>"*, %"struct.ap_uint<1>"*, [1 x i32]*, [2 x i32]*, i64*, i8*, i8*, i1*, i64*, i8*, i8*, i1*, i64*, i8*, i8*, i1*, i64*, i8*, i8*, i1*, i64*, i8*, i8*, i1*) #6 {
entry:
  %24 = alloca %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"
  %25 = alloca %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"
  %26 = alloca %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"
  %27 = alloca %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"
  %28 = alloca %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"
  call void @copy_out([1 x i32]* null, [1 x i32]* %2, [2 x i32]* null, [2 x i32]* %3, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %24, i64* %4, i8* %5, i8* %6, i1* %7, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %25, i64* %8, i8* %9, i8* %10, i1* %11, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %26, i64* %12, i8* %13, i8* %14, i1* %15, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %27, i64* %16, i8* %17, i8* %18, i1* %19, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %28, i64* %20, i8* %21, i8* %22, i1* %23)
  %29 = bitcast [1 x i32]* %2 to i32*
  %30 = bitcast [2 x i32]* %3 to i32*
  call void @hls_snn_izikevich_hw_stub(%"struct.ap_uint<1>"* %0, %"struct.ap_uint<1>"* %1, i32* %29, i32* %30, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %24, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %25, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %26, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %27, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %28)
  call void @copy_in([1 x i32]* null, [1 x i32]* %2, [2 x i32]* null, [2 x i32]* %3, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %24, i64* %4, i8* %5, i8* %6, i1* %7, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %25, i64* %8, i8* %9, i8* %10, i1* %11, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %26, i64* %12, i8* %13, i8* %14, i1* %15, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %27, i64* %16, i8* %17, i8* %18, i1* %19, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %28, i64* %20, i8* %21, i8* %22, i1* %23)
  ret void
}

declare void @hls_snn_izikevich_hw_stub(%"struct.ap_uint<1>"*, %"struct.ap_uint<1>"*, i32*, i32*, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"*, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"*, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"*, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"*, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"*)

; Function Attrs: noinline
define void @apatb_hls_snn_izikevich_ir(%"struct.ap_uint<1>"* %ret, %"struct.ap_uint<1>"* nocapture readonly %state, i32* noalias nocapture nonnull readonly "fpga.decayed.dim.hint"="1" %p_input, i32* noalias nocapture nonnull readonly "fpga.decayed.dim.hint"="2" %output_indexes, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias nocapture nonnull dereferenceable(16) %input_stream0, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias nocapture nonnull dereferenceable(16) %input_stream1, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias nocapture nonnull dereferenceable(16) %input_stream2, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias nocapture nonnull dereferenceable(16) %input_stream3, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* noalias nocapture nonnull dereferenceable(16) %output_stream) #7 {
entry:
  %p_input_copy = alloca [1 x i32], align 512
  %output_indexes_copy = alloca [2 x i32], align 512
  %input_stream0_copy.data = alloca i64
  %input_stream0_copy.keep = alloca i8
  %input_stream0_copy.strb = alloca i8
  %input_stream0_copy.last = alloca i1
  %input_stream1_copy.data = alloca i64
  %input_stream1_copy.keep = alloca i8
  %input_stream1_copy.strb = alloca i8
  %input_stream1_copy.last = alloca i1
  %input_stream2_copy.data = alloca i64
  %input_stream2_copy.keep = alloca i8
  %input_stream2_copy.strb = alloca i8
  %input_stream2_copy.last = alloca i1
  %input_stream3_copy.data = alloca i64
  %input_stream3_copy.keep = alloca i8
  %input_stream3_copy.strb = alloca i8
  %input_stream3_copy.last = alloca i1
  %output_stream_copy.data = alloca i64
  %output_stream_copy.keep = alloca i8
  %output_stream_copy.strb = alloca i8
  %output_stream_copy.last = alloca i1
  %0 = bitcast i32* %p_input to [1 x i32]*
  %1 = bitcast i32* %output_indexes to [2 x i32]*
  call fastcc void @copy_in([1 x i32]* nonnull %0, [1 x i32]* nonnull align 512 %p_input_copy, [2 x i32]* nonnull %1, [2 x i32]* nonnull align 512 %output_indexes_copy, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* nonnull %input_stream0, i64* %input_stream0_copy.data, i8* %input_stream0_copy.keep, i8* %input_stream0_copy.strb, i1* %input_stream0_copy.last, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* nonnull %input_stream1, i64* %input_stream1_copy.data, i8* %input_stream1_copy.keep, i8* %input_stream1_copy.strb, i1* %input_stream1_copy.last, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* nonnull %input_stream2, i64* %input_stream2_copy.data, i8* %input_stream2_copy.keep, i8* %input_stream2_copy.strb, i1* %input_stream2_copy.last, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* nonnull %input_stream3, i64* %input_stream3_copy.data, i8* %input_stream3_copy.keep, i8* %input_stream3_copy.strb, i1* %input_stream3_copy.last, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* nonnull %output_stream, i64* %output_stream_copy.data, i8* %output_stream_copy.keep, i8* %output_stream_copy.strb, i1* %output_stream_copy.last)
  %2 = alloca %"struct.ap_uint<1>"
  call void @apatb_hls_snn_izikevich_hw(%"struct.ap_uint<1>"* %2, %"struct.ap_uint<1>"* %state, [1 x i32]* %p_input_copy, [2 x i32]* %output_indexes_copy, i64* %input_stream0_copy.data, i8* %input_stream0_copy.keep, i8* %input_stream0_copy.strb, i1* %input_stream0_copy.last, i64* %input_stream1_copy.data, i8* %input_stream1_copy.keep, i8* %input_stream1_copy.strb, i1* %input_stream1_copy.last, i64* %input_stream2_copy.data, i8* %input_stream2_copy.keep, i8* %input_stream2_copy.strb, i1* %input_stream2_copy.last, i64* %input_stream3_copy.data, i8* %input_stream3_copy.keep, i8* %input_stream3_copy.strb, i1* %input_stream3_copy.last, i64* %output_stream_copy.data, i8* %output_stream_copy.keep, i8* %output_stream_copy.strb, i1* %output_stream_copy.last)
  %3 = load volatile %"struct.ap_uint<1>", %"struct.ap_uint<1>"* %2
  call void @copy_back([1 x i32]* %0, [1 x i32]* %p_input_copy, [2 x i32]* %1, [2 x i32]* %output_indexes_copy, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %input_stream0, i64* %input_stream0_copy.data, i8* %input_stream0_copy.keep, i8* %input_stream0_copy.strb, i1* %input_stream0_copy.last, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %input_stream1, i64* %input_stream1_copy.data, i8* %input_stream1_copy.keep, i8* %input_stream1_copy.strb, i1* %input_stream1_copy.last, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %input_stream2, i64* %input_stream2_copy.data, i8* %input_stream2_copy.keep, i8* %input_stream2_copy.strb, i1* %input_stream2_copy.last, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %input_stream3, i64* %input_stream3_copy.data, i8* %input_stream3_copy.keep, i8* %input_stream3_copy.strb, i1* %input_stream3_copy.last, %"class.hls::stream<hls::axis<ap_int<64>, 0, 0, 0>, 0>"* %output_stream, i64* %output_stream_copy.data, i8* %output_stream_copy.keep, i8* %output_stream_copy.strb, i1* %output_stream_copy.last)
  %4 = load volatile %"struct.ap_uint<1>", %"struct.ap_uint<1>"* %2
  store %"struct.ap_uint<1>" %4, %"struct.ap_uint<1>"* %ret
  ret void
}

declare i1 @fpga_fifo_not_empty_16(i8*)

declare i1 @fpga_fifo_not_empty_8(i8*)

declare void @fpga_fifo_pop_16(i8*, i8*)

declare void @fpga_fifo_pop_8(i8*, i8*)

declare void @fpga_fifo_pop_1(i8*, i8*)

declare void @fpga_fifo_push_16(i8*, i8*)

declare void @fpga_fifo_push_8(i8*, i8*)

declare void @fpga_fifo_push_1(i8*, i8*)

attributes #0 = { argmemonly noinline "fpga.wrapper.func"="copyin" }
attributes #1 = { argmemonly noinline norecurse "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #2 = { argmemonly noinline norecurse "fpga.wrapper.func"="arraycpy_hls" }
attributes #3 = { argmemonly noinline "fpga.wrapper.func"="copyout" }
attributes #4 = { argmemonly noinline "fpga.wrapper.func"="onebyonecpy_hls" }
attributes #5 = { argmemonly noinline "fpga.wrapper.func"="streamcpy_hls" }
attributes #6 = { "fpga.wrapper.func"="stub" }
attributes #7 = { noinline "fpga.wrapper.func"="wrapper" }

!llvm.dbg.cu = !{}
!llvm.ident = !{!0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0, !0}
!llvm.module.flags = !{!1, !2, !3}
!blackbox_cfg = !{!4}

!0 = !{!"clang version 7.0.0 "}
!1 = !{i32 2, !"Dwarf Version", i32 4}
!2 = !{i32 2, !"Debug Info Version", i32 3}
!3 = !{i32 1, !"wchar_size", i32 4}
!4 = !{}
!5 = distinct !{!5, !6}
!6 = !{!"llvm.loop.rotate.disable"}
