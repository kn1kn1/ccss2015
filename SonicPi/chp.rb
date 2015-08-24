# chp.rb
# Coded by Kenichi Kanai (kn1kn1) <kn1kn1@users.noreply.github.com>

bpm = 70

live_loop :mmm do
  in_thread do
    uncomment do
      if (bpm < 100)
        use_synth :saw
        echoes2(4, [:e2], 3)
      end
    end

    comment do
      if (bpm < 100)
        with_fx :distortion, mix: 1.0 do
          use_synth :beep
          echoes(12, [:b3, :b4, :e3, :e4], 0.075)
        end
      end
    end

    comment do
      if (bpm < 100)
        use_synth :saw
        echoes(8, [:b2, :e2], 0.5)
      end
    end
  end

  sleep 4
end

live_loop :sss do
  use_bpm bpm
  sync :ddd0

  16.times do
    unless rand < 0.5
      if rand < 0.001
        rate = 1
        phase = 0.5/[4,8,16].choose
      else
        rate = -1
        phase = 0.5/[2,3,4,4,8,16,32].choose
      end
      in_thread do
        with_fx:echo,
        phase:phase do
          sample :bd_tek,
            rate: rrand(0.2,1)*rate,
            sustain:0.25,amp:1
        end
      end
    end
    sleep 0.25
  end
end

rr = scale(:e10, :aeolian).shuffle
live_loop :ttt do
  use_bpm bpm
  sync :ddd0
  nn = rr.tick
  16.times do
    n = [2, 2, 2, 2, 4, 4, 8, 16].choose
    pan = rrand(-1,1)
    in_thread do
      with_fx :echo, phase: 0.5 / n, mix: rrand(0.8,1) do
        chp :tri, nn, 0.125, 0.3, pan
      end
    end
    sleep 0.25
  end
end


live_loop :ddd do |idxd|
  use_bpm bpm
  cue :ddd0
  i = idxd % 8
  with_fx :rlpf, cutoff: 40 + i * 10, cutoff_slide: 1 do |c|
    [
      [1,0,1,0,0,0,0,0],
      [0,1,0,1,0,0,0,0],
      [0,0,1,0,0,0,0,0],
      [1,0,0,1,0,0,0,0]
    ].each.with_index do |pat, j|
      pat.each.with_index do |kick, k|
        bd if kick == 1
        sd if k == 4
        #        sd rrand(0.3, 0.6) if i == 7 && j == 3 && k == 1
        sleep 0.125
      end
    end

    idxd = idxd + 0.5
  end
end

define :chp do |synth, note, dur, amp, pan=0|
  use_synth synth
  pp = play note, amp: amp, pan: pan,
    release: dur, note_slide_shape: 7
  control pp, note: 12, note_slide: dur
end

define :echoes2 do |num, tonics, amp=1|
  num.times do
    play chord(tonics.choose, [:m11, :m9, :major, :major7].choose),
      attack: [1, 0.75, 1.25, 1.5, 2].choose, cutoff: 80,
      amp: amp, pan: rrand(-0.2,0.2)
    sleep 1
  end
end

define :echoes do |num, tonics, amp=1|
  num.times do
    use_bpm bpm
    sleep [0, 0.5, 0.75, 1, 1.25].choose
    rnote = chord(tonics.choose, :major).choose
    puts rnote
    rel = rrand(1.5, 3)
    play rnote,
      amp: amp, pan: rrand(-0.2, 0.2),
      attack: 0.25, release: rel
  end
end

define :bd do
  chp :beep, 35, 1, 5
  chp :fm, 80, 0.125, 10
end

define :sd do |amp=2|
  with_fx :distortion do
    chp :saw, 100, 0.125, amp
  end
end
