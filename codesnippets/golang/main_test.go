package main

import (
	"testing"
	"time"
)

func TestTimeToString(t *testing.T) {
	type args struct {
		time *time.Time
	}
	tests := []struct {
		name string
		args args
		want string
	}{
		// TODO: Add test cases.
	}
	for _, tt := range tests {
		t.Run(tt.name, func(t *testing.T) {
			if got := TimeToString(tt.args.time); got != tt.want {
				t.Errorf("TimeToString() = %v, want %v", got, tt.want)
			}
		})
	}
}
