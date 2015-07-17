#!/usr/bin/perl

############### log calculation ############## 

sub log10 {
    my $n = shift;
    return log($n)/log(10);
}

###################################################################
####################### file input ################################
###################################################################

($basefile, $noisefile, $outfile, $bgmfile, $snr) = @ARGV;

open(BASE, "$basefile");
open(NOISE, "$noisefile");
open(OUT, ">$outfile");
open(BGM, ">$bgmfile");

# 音声(ベース)ファイルの読み込み
$t = 0;
$baseenergy = 0;
while (read(BASE, $buf, 2)) {
    ($nbuf) = unpack("s", $buf); # バイナリから10進数に変換
                                 # 符号付きshortと仮定
    # print "$nbuf\n";
    $base[$t] = $nbuf;
    $baseenergy += $base[$t] * $base[$t];  
    $t++;
}

$basesize = $t - 1;   # 音声ファイルのサイズ


# 雑音ファイルの読み込み
$t = 0;
while (read(NOISE, $buf, 2)) {
    ($nbuf) = unpack("s", $buf); # バイナリから10進数に変換
                                 # 符号付きshortと仮定
    # printf "$nbuf\n";
    $noise[$t] = $nbuf;
    $t++;
}

$noisemax = $t - 1; # 雑音ファイルのサイズ


#####################################################################
######################### S/N calculation ###########################
##################################################################### 

$HIGH_VALUE = $noisemax - $basesize - 1;
$LOW_VALUE = 0;

$noisestart = int(($HIGH_VALUE - $LOW_VALUE + 1) * rand(1) + $LOW_VALUE);
########################## noise star point detection ###############
# print "$noisestart\n";
# print "$basesize\n";
# print "$noisemax\n";

$t = $noisestart;
$noiseenergy = 0;
while () {
    $noiseenergy += $noise[$t] * $noise[$t];
    $t++;
    if ($t - $noisestart == $basesize) {
	last;
    }
}
# $noiseavg = $noiseenergy / $basesize;

# $t = $noisestart;
# $noisebunsan = 0;

# while () {
#    $noisebunsan = $noisebunsan + ($noise[$t] - $noiseavg) * ($noise[$t] - $noiseavg);
#    $t++;
#    if ($t - $noisestart == $basesize) {
#	last;
#    }
# }

# $noisehensa = sqrt($noisebunsan / $basesize);
# ($noise[$nt] - $noiseavg) / $noisehensa * $baseavg / (20 ** ($snr /10));


#####################################################################
######################### wave  write ###############################
#####################################################################

$t = 0;
$nt = $noisestart;
$amp = sqrt($baseenergy / (10 ** ($snr /10)) / $noiseenergy);

$baseenergy = 0;
$noiseenergy = 0;
# $tmp = 0;

while () {
    # $tmp = $tmp + ($noise[$nt] - $noiseavg) / $noisehensa;
    $tmp = $noise[$nt] * $amp;

    # 雑音重畳データ
    $out[$t] = $base[$t] + $tmp;

    # 実際のSNR計算用
    $baseenergy += $base[$t] * $base[$t];
    $noiseenergy += $tmp * $tmp;

    # 符号付きshortに変換して書き出し
    $buf = pack "s", $out[$t];
    syswrite OUT, $buf, 2;

    $buf = pack "s", $tmp;
    syswrite BGM, $buf, 2;

    $t++;
    $nt++;
    if ($t == $basesize) {
	last;
    }
}

$snr = 10 * &log10($baseenergy / $noiseenergy);

# $tmpavg = $tmp / $basesize;
# $nt = $noisestart;
# $tmpbunsan = 0;

# while () {
#    $tmpbunsan = $tmpbunsan + (($noise[$nt] - $noiseavg) / $noisehensa - $tmpavg) * (($noise[$nt] - $noiseavg) / $noisehensa - $tmpavg);
#    $nt++;
#    if ($nt - $noisestart == $basesize) {
#	last;
#    }
# }

# $tmphensa = sqrt($tmpbunsan/$basesize);

# print "tmp->$tmphensa\n";
# print "$noiseavg\n";
# print "$noisehensa\n";
# print "$snr\n";

close(BASE);
close(NOISE);
close(OUT);
close(BGM);

print "$outfile $noisefile $noisestart $amp $snr\n";
