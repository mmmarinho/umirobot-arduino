#pragma once
/**
(c) 2022, Murilo M. Marinho.

    This file is part of umirobot-arduino.

    umirobot-arduino is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    umirobot-arduino is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with umirobot-arduino.  If not, see <https://www.gnu.org/licenses/>.
*/

template <class T, int N>
constexpr int get_size_of_array(T (&)[N])
{
    // https://stackoverflow.com/questions/49454005/how-to-get-an-array-size-at-compile-time
    return N;
}

template <class T, int N>
constexpr bool check_digital_in_port_mode_impl(const T (&t)[N], const int& n)
{
    return n == -1 ? true : (((t[n]==INPUT || t[n]==INPUT_PULLUP)) && check_digital_in_port_mode_impl(t, n - 1));
}

template <class T, int N>
constexpr bool check_digital_in_port_modes(const T (&t)[N])
{
    return check_digital_in_port_mode_impl(t, N - 1);
}